import { z } from 'npm:zod';
import { CMD_RECEIVE } from '../COMMANDS.ts';
import { Func } from './types.ts';

export function getHandleFunction(obj: any) {
  const handle = <T extends keyof typeof CMD_RECEIVE>(
    type: T,
    cb: Func<[z.infer<(typeof CMD_RECEIVE)[T]>], void>
  ) => {
    if (type !== obj.type) return;
    const val = CMD_RECEIVE[type];

    const { success, data } = val.safeParse(obj.data);
    if (!success) return;

    cb(data);
  };

  return handle;
}
