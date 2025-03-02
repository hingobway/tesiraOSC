import { Buffer } from 'node:buffer';
const dst = '169.254.3.243';
const port = 23;

console.log('connecting...');

const TELNET_INIT = Buffer.from(
  'fffb25fffd03fffb18fffb1ffffb20fffb21fffb22fffb27fffd05',
  'hex'
);

const c = await Deno.connect({
  transport: 'tcp',
  port,
  hostname: dst,
});

await c.write(TELNET_INIT);

console.log('connected');

setInterval(() => {}, 5);
