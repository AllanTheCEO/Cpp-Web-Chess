import React, { useEffect, useState } from "react";


// Initialize the WASM module exactly once and reuse it
const cppReady = (window.__cppReady ||= window.initCppJs({ path: "./dist" }));

// Optional: map piece letters to image URLs (put your SVGs under /pieces)
const IMG = {
    'P': "./assets/wp.svg", 'N': "./assets/wn.svg", 'B': "./assets/wb.svg",
    'R': "./assets/wr.svg", 'Q': "./assets/wq.svg", 'K': "./assets/wk.svg",
    'p': "./assets/bp.svg", 'n': "./assets/bn.svg", 'b': "./assets/bb.svg",
    'r': "./assets/br.svg", 'q': "./assets/bq.svg", 'k': "./assets/bk.svg",
  ' ': null
};



export default function App({onMove, serverFen, myColor, hasTwoPlayers,
   onReset, resetNonce, serverGameOverMsg}) {
  const [selected, setSelected] = useState(null);
  const [status, setStatus] = useState("initializing…");
  const [gameOver, setGameOver] = useState(null);
  const [promotion, setPromotion] = useState(null);
  const [sideToMove, setSideToMove] = useState("W");
  

  useEffect(() => {
    let alive = true;
    (async () => {
      const api = await cppReady;              // <- module is ready here

      // Create one Board instance and keep it around
      const { WasmBoard } = api;                 // ← wrapper
      const b = new WasmBoard();

      b.initializeBoard?.();
      window.__board = b;

      if (serverFen) {
        b.parseFEN?.(serverFen);
      }


      
      if (typeof b.setGameOverCallback === "function") {
        b.setGameOverCallback((msg) => {
          if (msg) { setGameOver(msg); setStatus(msg); }
        });
      }
      window.__board = b;

      if (alive) setStatus("ready");
    })().catch(err => {
      console.error(err);
      if (alive) setStatus("Init failed: " + (err?.message || err));
    });
    return () => { alive = false; };
  }, []);

  useEffect(() => {
    if (typeof serverGameOverMsg === "string" && serverGameOverMsg) {
      setGameOver(serverGameOverMsg);
      setStatus(serverGameOverMsg);
    }
  }, [serverGameOverMsg]);

  const size  = 8;
  const light = "#ffffff";
  const dark  = "#074b19ff";

  function getPiece(r, c) {
    try {
      const b = window.__board;
      if (!b) return ' ';
      if (typeof b.getPiece === "function") return b.getPiece(r, c); // preferred
    } catch { /* ignore */ }
    return ' ';
  }

  function colorOf(r, c) {
    if (String.fromCharCode(getPiece(r, c)) === ' ') {
      return ' ';
    }
    if (String.fromCharCode(getPiece(r, c)) === String.fromCharCode(getPiece(r, c)).toUpperCase()){
      return "W";
    } else {
      return "B";
    }
  }


  async function onCellClick(r, c){
    if (gameOver) return;

    if (!myColor || myColor === "spectator") {
      setStatus("In spectator mode: can't move");
      return;
    }
    
    if (!hasTwoPlayers) {
      setStatus("Waiting for opponent");
      return;
    } else {
      setStatus("Your turn");
    }

    if (myColor !== sideToMove) {
      setStatus("Not your turn");
      return;
    }

    const piece = getPiece(r, c);
    const color = colorOf(r, c);

    if(!selected){
      if (!myColor || myColor === "spectator") return; // can't move
      if (color !== myColor) return;
      setSelected({r, c, color});
      return;
    }

    const selPiece = getPiece(selected.r, selected.c);
    const selColor = colorOf(selected.r, selected.c);
    if((String.fromCharCode(piece) === 'R' && String.fromCharCode(selPiece) === 'K' && color === selColor) ||
     (String.fromCharCode(piece) === 'r' && String.fromCharCode(selPiece) === 'k' && color === selColor)) {
      handleCastle(selected.r, selected.c, r, c);
      setSelected(null); 
    }
    if (piece != ' ' && color === selColor) {
      setSelected({ r, c, color });
      return;
    }
    handleMove(selected.r, selected.c, r, c);
    setSelected(null); 
  }

  useEffect(() => {
    if (!serverFen) return;

    const parts = serverFen.split(" ");
    if (parts.length >= 2) {
      setSideToMove(parts[1] === "w" ? "W" : "B");
    }
      
    // your existing setFEN → WASM call
    window.__board?.parseFEN?.(serverFen);

    setSelected(null);
    setPromotion(null);

    const b = window.__board;
    const msg = (typeof b?.gameOver === "function") ? b.gameOver() : "";
    if (msg) { setGameOver(msg); setStatus(msg); }

  }, [serverFen]);

  useEffect(() => {
    (async () => {
      setSelected(null);
      setPromotion(null);
      setGameOver(null);
      await resetGame();                 // wait for new board
      window.__board?.parseFEN?.(serverFen); // apply authoritative FEN (startingFEN)
      setStatus("ready");
    })();
  }, [resetNonce]);

  function handleMove(sr, sc, er, ec) {
    const b = window.__board;
    b.movePiece(sr, sc, er, ec);


    //Check for pending promotion
    let isPromotion = false;
    if (String.fromCharCode(getPiece(er, ec)) === 'P' && er === 7) {
      isPromotion = true;
    } else if (String.fromCharCode(getPiece(er, ec)) === 'p' && er === 0) {
      isPromotion = true;
    }
    if (isPromotion) { 
      setPromotion({ row: er, col: ec, color: colorOf(er, ec) });
    }

    //Check for game over
    const msg = (typeof b.consumeGameOver === "function") ? b.consumeGameOver() : "";
    if (msg) { setGameOver(msg); setStatus(msg); }

    const newFen = b.getFEN()

    if (onMove) {
      onMove(newFen, msg);
    }
  }

  function handlePromotion(piece) {
    let char = piece.charCodeAt(0);
    console.log(piece);
    const b = window.__board;
    b.promotePawn(promotion.row, promotion.col, char);
    b.finalizeAfterPromotion(promotion.color);
    const msg = typeof b.consumeGameOver === "function" ? b.consumeGameOver() : "";
    if (msg) { setGameOver(msg); setStatus(msg); }
    setPromotion(null);
    const newFen = b.getFEN();
    onMove?.(newFen, msg || "");
  }

  function handleCastle(kr, kc, rr, rc) {
    const b = window.__board;
    b.castle(kr, kc, rr, rc);

    const msg = (typeof b.consumeGameOver === "function") ? b.consumeGameOver() : "";
    if (msg) { setGameOver(msg); setStatus(msg); }

    const newFen = b.getFEN();
    if (onMove) {
      onMove(newFen, msg);
    }
  }

  async function resetGame() {
    const api = await (window.__cppReady ||= window.initCppJs({ path: "./dist" }));
    const { WasmBoard, Board } = api;
    const Ctor = WasmBoard || Board;

    if (window.__board && typeof window.__board.delete === "function") {
      window.__board.delete();
    }

    // 3) Create a brand-new board and initialize it
    const b = new Ctor();
    b.initializeBoard?.();
    window.__board = b;

    setSelected(null);
    setGameOver(null);
    setStatus("ready");

    
  }


  useEffect(() => {
    window.__selected = selected;       // inspect in console as __selected
    console.log("selected:", selected); // optional live log
  }, [selected]);

  const cells = [];
  for (let r = 7; r >= 0; r--) {
    for (let c = 0; c < size; c++) {
      const isWhite = ((r + c) % 2) === 1;
      const piece = String.fromCharCode(getPiece(r, c));
      const image = IMG[piece] || null;
      const isSelected = selected && selected.r === r && selected.c === c;

      cells.push(
        <div
          key={`${r}-${c}`}
          style={{
            position: "relative",
            backgroundColor: isWhite ? light : dark,
            outline: isSelected ? "3px solid #ffd54a" : "none",
          }}
          onClick={() => onCellClick(r, c)} 
          title={`${r},${c} ${piece || ''}`}
        >
          {image && (
            <img
              src={image}
              alt={piece}
              style={{
                position: "absolute",
                inset: 0,
                margin: "auto",
                width: "85%",
                height: "85%",
                objectFit: "contain",
                pointerEvents: "none"
              }}
            />
          )}
        </div>
      );
    }
  }

  function setFEN(fen) { 
    const b = window.__board;
    const isValid = b.parseFEN(fen);
    if (!isValid) {
      setStatus("Invalid FEN string");
    } else {
      setStatus("FEN set successfully");
    }
  }
  
  function fenInputBox() {
    const [inputValue, setInputValue] = useState('');
    const [committedValue, setCommittedValue] = useState('');

    return (
      <div>
        <input
          type="text"
          value={inputValue}
          onChange={(e) => setInputValue(e.target.value)}
          onKeyDown={(e) => {
              if(e.key === "Enter") {
                setCommittedValue(inputValue);
                setFEN(inputValue)
              }
            }
          }
          placeholder="Enter text here"
        />
        <p>Committed value: {committedValue}</p>
      </div>
    );
  }


  const capturedWhitePieces = window.__board ? window.__board.whiteCapturedPieces : [];
  const capturedBlackPieces = window.__board ? window.__board.blackCapturedPieces : [];
  function pieceValue(piece) {
    switch(piece) {
      case 'P': return 1;
      case 'N': return 3;
      case 'B': return 3;
      case 'R': return 5;
      case 'Q': return 9;
      case 'K': return 0;
      default:  return 0;
    }
  }

  //capturedWhitePieces.sort((a, b) => pieceValue(a) - pieceValue(b));
  //capturedBlackPieces.sort((a, b) => pieceValue(a) - pieceValue(b));

  

  return (
  <div
    style={{
      position: "fixed",
      inset: 0,
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
      background: "#1d1818ff"
    }} 
  >
    {/* Captured Chess Pieces */}
    <div 
      style = {{
        display: "flex",
        flexDirection: "column",  // stack vertically
        alignItems: "center",
        gap: 12,
        marginRight: 20
      }}
    >
      
    </div>

    {/* Center column for FEN + board + status */}
    <div
      style={{
        display: "flex",
        flexDirection: "column", // stack vertically
        alignItems: "center",
        gap: 12
      }}
    >
      {/* FEN input on top */}
      <div>
        {fenInputBox()}
      </div>

      {/* Board in the middle */}
      <div
        style={{
          width: "80vmin",
          height: "80vmin",
          display: "grid",
          gridTemplateColumns: `repeat(${size}, 1fr)`,
          gridTemplateRows: `repeat(${size}, 1fr)`
        }}
      >
        {cells}
      </div>

      {/* Status text below */}
      <pre style={{ margin: 0 }}>{status}</pre>
    </div>
    
    {/*Promotion overlay */}
    {promotion && (
      <div 
        style = {{
          position: "fixed",
          inset: 0,
          background: "rgba(95, 110, 9, 0.6)",
          display: "grid",
          placeItems: "center",
          zIndex: 1000
        }}
      >
        <div 
          style = {{
            background: "#222",
            color: "#fff",
            padding: 16,
            borderRadius: 8,
            textAlign: "center",
            minWidth: 240,
          }}
        >
          <p>
            {promotion.color === "W" ? "White" : "Black"} pawn promotion at (
            {promotion.row},{promotion.col})            
          </p>
          <div style={{ display: "flex", gap: 8, justifyContent: "center" }}>
            {['N', 'B', 'R', 'Q'].map((p) => (
              <button
                key={p}
                onClick={() => handlePromotion(p)}
              >
                {p}
              </button>
            ))}
          </div>
        </div>
      </div>
    )}
    

    {gameOver && (
      <div
        style={{
          position: "fixed",
          inset: 0,
          background: "rgba(0,0,0,.6)",
          display: "grid",
          placeItems: "center",
          zIndex: 9999
        }}
      >
        <div
          style={{
            background: "#222",
            color: "#fff",
            padding: 24,
            borderRadius: 12,
            minWidth: 320,
            textAlign: "center",
            boxShadow: "0 10px 30px rgba(0,0,0,.5)"
          }}
        >
          <h2 style={{ margin: "0 0 8px" }}>{gameOver}</h2>
          <p style={{ margin: "0 0 16px", opacity: 0.8 }}>Game ended.</p>
          <button
            onClick={() => onReset?.()}
            style={{
              padding: "8px 16px",
              borderRadius: 8,
              cursor: "pointer"
            }}
          >
            Reset board
          </button>
        </div>
      </div>
    )}
  </div>
);

}
