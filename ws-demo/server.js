// server.js
const WebSocket = require("ws");

const wss = new WebSocket.Server({ port: 8080 });

const games = new Map();
const startingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

function broadcastPresence(id) {
  const game = games.get(id);
  if (!game) return;
  const hasTwoPlayers = !!(game.white && game.black);

  for (const player of game.players) {
    if (player.readyState === WebSocket.OPEN) {
      player.send(
        JSON.stringify({
          type: "presence",
          gameId: id,
          hasTwoPlayers,
          hasWhitePlayer: !!game.white,
          hasBlackPlayer: !!game.black,
        })
      );
    }
  }
}

wss.on("connection", (ws, req) => {
  console.log("New client connected from", req.socket.remoteAddress);

  ws.send("Hello from server: WebSocket connection established.");

  ws.on("message", (data) => {
    const text = data.toString();

    let msg;
    try {
      msg = JSON.parse(text);
    } catch {
      console.log("Bad JSON:", text);
      return;
    }

    if (msg.type === "create_game") {
      const id = msg.gameId;
      if (!id) return;

      let game = games.get(id);
      if (!game) {
        game = { fen: startingFEN, players: new Set(), white: null, black: null };
        games.set(id, game);
        console.log("Created game", id);
      } else {
        console.log("Joining existing game", id);
      }

      let color = "spectator"
      if (!game.white) {
        game.white = ws;
        color = "W";
      } else if (!game.black) {
        game.black = ws;
        color = "B";
      }      

      game.players.add(ws)
      ws.currentGameId = id;
      ws.color = color;
      
      ws.send(JSON.stringify({
        type: "fen",
        gameId: id, 
        fen: game.fen, 
        color,
        hasTwoPlayers: !!(game.white && game.black)
      }) );
      broadcastPresence(id)
      return;
    }

    if (msg.type === "reset") {
      const id = msg.gameId || ws.currentGameId;
      if (!id) return;

      const game = games.get(id);
      if (!game) return;

      if (ws.color !== "W" && ws.color !== "B") {
        ws.send(
          JSON.stringify({ type: "error", message: "Spectators can't reset." })
        );
        return;
      }

      game.fen = startingFEN;

      const hasTwoPlayers = !!(game.white && game.black);
      for (const client of game.players) {
        if (client.readyState === WebSocket.OPEN) {
          client.send(
            JSON.stringify({
              type: "fen",
              gameId: id,
              fen: game.fen,
              hasTwoPlayers,
              reset: true,
              gameOverMsg: ""
            })
          );
        }
      }
      return
    }

    if (msg.type === "move") {
      const id = msg.gameId || ws.currentGameId;
      const gameOverMsg = (typeof msg.gameOverMsg === "string") ? msg.gameOverMsg : "";
      if (!id) return;

      const game = games.get(id);
      if (!game) {
        console.log("Move for unknown game", id);
        return;
      }

      if (ws.color !== "W" && ws.color !== "B") {
        ws.send(
          JSON.stringify({ type: "error", message: "Spectators can't move." })
        );
        return;
      }

      if (!(game.white && game.black)) {
        ws.send(
          JSON.stringify({type: "error", message: "Waiting for opponent."})
        );
        return;
      }

      const oldFen = game.fen || startingFEN;
      const preSide = oldFen.split(" ")[1] === "w" ? "W" : "B";

      if (ws.color !== preSide) {
        ws.send(
          JSON.stringify({ type: "error", message: "Not your turn." })
        );
        return;
      }

      game.fen = msg.fen;

      // Broadcast updated FEN to everyone in that game
      const hasTwoPlayers = !!(game.white && game.black);
      for (const client of game.players) {
        if (client.readyState === WebSocket.OPEN) {
          client.send(
            JSON.stringify({
              type: "fen",
              gameId: id,
              fen: game.fen,
              hasTwoPlayers,
              gameOverMsg
            })
          );
        }
      }
      return;
    }

    
  });


  ws.on("close", () => {
    console.log("Client disconnected");
    const id = ws.currentGameId;
    if (!id) return;
    const game = games.get(id);
    if (!game) return;
    game.players.delete(ws);
    if (game.white === ws) game.white = null;
    if (game.black === ws) game.black = null;
    if (game.players.size === 0) games.delete(id);
    broadcastPresence(id);
  });

  ws.on("error", (err) => {
    console.error("WebSocket error:", err);
  });
});

console.log("WebSocket server listening on ws://localhost:8080");
