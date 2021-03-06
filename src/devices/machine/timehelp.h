// license:BSD-3-Clause
// copyright-holders:Aaron Giles,smf
/***************************************************************************

	timehelp.h

	Assorted shared functionality between timekeeping chips and RTCs.

***************************************************************************/

#pragma once

#ifndef SRC_DEVICES_MACHINE_TIMEHELP_H
#define SRC_DEVICES_MACHINE_TIMEHELP_H

class time_helper
{
public:
	static inline UINT8 make_bcd(UINT8 data)
	{
		return (((data / 10) % 10) << 4) + (data % 10);
	}

	static inline UINT8 from_bcd(UINT8 data)
	{
		return (((data >> 4) & 15) * 10) + (data & 15);
	}

	static int inc_bcd(UINT8 *data, int mask, int min, int max)
	{
		int bcd = (*data + 1) & mask;
		int carry = 0;

		if ((bcd & 0x0f) > 9)
		{
			bcd &= 0xf0;
			bcd += 0x10;
			if (bcd > max)
			{
				bcd = min;
				carry = 1;
			}
		}

		*data = (*data & ~mask) | (bcd & mask);
		return carry;
	}

};

#endif // SRC_DEVICES_MACHINE_TIMEHELP_H