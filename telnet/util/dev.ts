import 'jsr:@std/dotenv/load';

export const FAKE_TELNET = Deno.env.get('FAKE_TELNET');
