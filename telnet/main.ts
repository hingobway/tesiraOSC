import { TesiraWrapper } from './tesira.ts';
import { Sockets } from './sockets.ts';
import { Routing } from './Routing.ts';

// GET PORT
const port = parseInt(Deno.args[0]);
if (!Number.isFinite(port)) {
  console.error('MISSING IPC PORT');
  Deno.exit();
}

// CONNECTIONS INIT
const tesira = new TesiraWrapper();
const ipc = new Sockets();
const routes = new Routing(tesira, ipc);

// IPC HANDLING
ipc.listen('message', (e) => {
  let obj;
  try {
    obj = JSON.parse(e.data);
  } catch (_) {
    return;
  }
  if (!(typeof obj?.type === 'string')) return;

  routes.IPCHandlers(obj);
});

// TELNET HANDLING
routes.TesiraHandlers();

// SERVE WS
Deno.serve({ port }, (req) => {
  if (req.headers.get('upgrade') != 'websocket')
    return new Response(null, { status: 501 });

  const { socket, response } = Deno.upgradeWebSocket(req);

  socket.addEventListener('open', () => {
    ipc.addSocket(socket);
  });

  return response;
});
