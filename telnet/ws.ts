Deno.serve(
  {
    port: 53533,
    hostname: '127.0.0.1',
  },
  (req) => {
    if (req.headers.get('upgrade') != 'websocket')
      return new Response(null, { status: 501 });

    const { socket, response } = Deno.upgradeWebSocket(req);

    socket.addEventListener('open', () => {
      console.log('new connection!');
    });

    socket.addEventListener('message', (e) => {
      console.log('MESSAGE', e.data);

      socket.send('received!');
    });

    return response;
  }
);
