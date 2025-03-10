import { TesiraWrapper } from './tesira.ts';
import { Sockets } from './sockets.ts';

import { getHandleFunction } from './COMMANDS.ts';

// GET PORT
const port = parseInt(Deno.args[0]);
if (!Number.isFinite(port)) {
  console.error('MISSING IPC PORT');
  Deno.exit();
}

const tesira = new TesiraWrapper();
const sockets = new Sockets();

sockets.listen('message', (e) => {
  let obj;
  try {
    obj = JSON.parse(e.data);
  } catch (_) {
    return;
  }
  if (!(typeof obj?.type === 'string')) return;
  const handle = getHandleFunction(obj);

  // COMMAND HANDLERS

  handle('tesira_connect', (config) => {
    tesira.startup(config);
  });

  handle('tesira_run', ({ message }) => {
    tesira.sendMessage(message);
  });
});

// TELNET HANDLERS

tesira.on('connected', () => {
  sockets.send('tesira_connect_status', { connected: true });
});
tesira.on('disconnect', () => {
  sockets.send('tesira_connect_status', { connected: false });
});

// SERVE WS

Deno.serve({ port }, (req) => {
  if (req.headers.get('upgrade') != 'websocket')
    return new Response(null, { status: 501 });

  const { socket, response } = Deno.upgradeWebSocket(req);

  socket.addEventListener('open', () => {
    sockets.addSocket(socket);
  });

  return response;
});
