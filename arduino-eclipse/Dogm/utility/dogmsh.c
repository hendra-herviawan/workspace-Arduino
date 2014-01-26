/*

  dogmsh.c

  (c) 2010 Oliver Kraus (olikraus@gmail.com)
  
  This file is part of the dogm128 Arduino library.

  The dogm128 Arduino library is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  The dogm128 Arduino library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  Lesser GNU General Public License for more details.

  You should have received a copy of the Lesser GNU General Public License
  along with dogm128.  If not, see <http://www.gnu.org/licenses/>.


*/

#include "dogm128.h"

/* x1 must be lower or equal to x2 */
void dog_SetHLine(uint8_t x1, uint8_t x2, uint8_t y)
{
  uint8_t tmp, x;
  if ( x1 < dog_width )
    if ( y >= dog_min_y && y <=dog_max_y )
    {
      tmp = y;
      tmp &= (uint8_t)7;
      tmp = dog_get_bit_to_mask()[tmp];
      
      if ( x2 > dog_width-1 )
	x2 = dog_width-1;
      for( x = x1; x <= x2; x++ )
	dog_page_buffer[x] |= tmp;
    }  
}


