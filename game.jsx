import React, { useEffect, useRef, useState } from "react";
import App from "./app.jsx";

export default function Game() {
    const [gameId, setGameId] = useState("");
    const [joinedGameId, setJoinedGameId] = useState(null);
    const [fen, setFen] = useState(null)
    const [capturedWhitePieces, setCapturedWhitePieces] = useState([]);
    const [capturedBlackPieces, setCapturedBlackPieces] = useState([]);
    const [myColor, setMyColor] = useState(null);
    const [hasTwoPlayers, setHasTwoPlayers] = useState(false);
    const [resetNonce, setResetNonce] = useState(0);
    const [serverGameOverMsg, setServerGameOverMsg] = useState("");
    const wsRef = useRef(null);
    

    
    useEffect(() => {
        const ws = new WebSocket("ws://localhost:8080");
        wsRef.current = ws;
        ws.onopen = () => {
            console.log("WebSocket connection established");
        };
        ws.onmessage = (event) => {
            console.log("Msg from Server: " + event.data)
            let msg;
            try {
                msg = JSON.parse(event.data);
            } catch (e) {
                msg = event;
                return;
            }

            if (msg.type === "fen") {
                if (msg.color && !myColor) {
                    setMyColor(msg.color);
                }
                if (typeof msg.hasTwoPlayers === "boolean") {
                setHasTwoPlayers(msg.hasTwoPlayers);
                }

                if ("gameOverMsg" in msg && typeof msg.gameOverMsg === "string") {
                setServerGameOverMsg(msg.gameOverMsg);
                } else {
                setServerGameOverMsg("");
                }
                if (msg.reset) {
                    setResetNonce(n => n + 1);
                    setServerGameOverMsg("");
                }
                setFen(msg.fen);
            }

            if (msg.type === "presence") {
                if (typeof msg.hasTwoPlayers === "boolean") {
                    setHasTwoPlayers(msg.hasTwoPlayers);
                }
            }
        };
        ws.onclose = () => {
            console.log("WebSocket connection closed");
        };
        ws.onerror = (error) => {
            console.error("WebSocket error:", error);
        };

    }, []);


    const handleCreateGame = (event) => {
        setGameId(event.target.value);
    }

    const sendReset = () => {
        if (!joinedGameId) return;
        sendMessage({ type: "reset", gameId: joinedGameId });
    }

    const handleKeyDown = (event) => {
        if (event.key === "Enter") {
            const id = gameId.trim();
            if (!id) return;

            const ws = wsRef.current;

            if (ws && ws.readyState === WebSocket.OPEN) {
                sendMessage({ type: "create_game", gameId: id }); // join-or-create
                setJoinedGameId(id);
                setGameId("");
            }

        }
    }

    function sendMessage(message) {
        const ws = wsRef.current;
        if (ws && ws.readyState === WebSocket.OPEN) {
            ws.send(JSON.stringify(message));
        }
    }
    
    const sendMove = (fen, gameOverMsg) => {
        const ws = wsRef.current;
        if (ws && ws.readyState === WebSocket.OPEN && joinedGameId) {
            ws.send(JSON.stringify({
            type: "move",
            gameId: joinedGameId,
            fen,
            gameOverMsg
            }));
        }
    }


    if (fen) {
        return (
            <App
                onMove = {sendMove}
                serverFen = {fen}
                myColor = {myColor}
                hasTwoPlayers = {hasTwoPlayers}
                onReset={sendReset}
                resetNonce={resetNonce}
                serverGameOverMsg={serverGameOverMsg}
            />
        )
    }

    return(
        
        <div 
            style={{
                display: "flex",
                flexDirection: "column",
                alignItems: "center",
                justifyContent: "center",
                height: "100vh",
                backgroundColor: "#3d3d3dff",
            }}>
            <h1>Create Game</h1>
            <input 
            type="text" 
            value = {gameId}
            onChange={handleCreateGame}
            onKeyDown={handleKeyDown}
            placeholder="Game ID" />
            <p>Game ID: {gameId}</p>
        </div>);
}

