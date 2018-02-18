/*
 * Copyright (C) 2007 David Shaw <dshaw@jabberwocky.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha1.h"
#include "output.h"
#include "packets.h"

extern int verbose;

void *
xrealloc(void *ptr,size_t size)
{
  ptr=realloc(ptr,size);
  if(!ptr)
    {
      fprintf(stderr,"Unable to allocate memory\n");
      abort();
    }

  return ptr;
}

struct packet *
append_packet(struct packet *packet,unsigned char *buf,size_t len)
{
  if(packet)
    {
      while(packet->size-packet->len<len)
	{
	  packet->size+=100;
	  packet->buf=xrealloc(packet->buf,packet->size);
	}

      memcpy(&packet->buf[packet->len],buf,len);
      packet->len+=len;
    }
  else
    {
      packet=xmalloc(sizeof(*packet));
      packet->type=0;
      packet->buf=xmalloc(len);
      packet->len=len;
      packet->size=len;

      memcpy(packet->buf,buf,len);
    }

  return packet;
}

void
free_packet(struct packet *packet)
{
  if(packet)
    {
      free(packet->buf);
      free(packet);
    }
}
