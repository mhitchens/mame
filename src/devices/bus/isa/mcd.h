// license:BSD-3-Clause
// copyright-holders:Carl
#pragma once

#ifndef __MCD_H__
#define __MCD_H__

#include "emu.h"
#include "isa.h"
#include "imagedev/chd_cd.h"

//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> mcd_isa_device

class mcd_isa_device : public cdrom_image_device,
	public device_isa16_card_interface
{
public:
	// construction/destruction
	mcd_isa_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	// optional information overrides
	virtual ioport_constructor device_input_ports() const override;

	DECLARE_ADDRESS_MAP(map, 16);

	DECLARE_READ8_MEMBER(data_r);
	DECLARE_READ8_MEMBER(flag_r);
	DECLARE_WRITE8_MEMBER(cmd_w);
	DECLARE_WRITE8_MEMBER(reset_w);
	virtual UINT16 dack16_r(int line) override;
protected:
	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
private:
	bool read_sector(bool first = false);

	bool m_change;
	bool m_newstat;
	bool m_data;
	UINT8 m_stat;
	UINT8 m_buf[2352];
	int m_buf_count;
	int m_buf_idx;
	UINT8 m_cmdbuf[16];
	int m_cmdbuf_count;
	int m_cmdrd_count;
	int m_cmdbuf_idx;
	UINT8 m_mode;
	UINT8 m_cmd;
	UINT8 m_conf;
	UINT8 m_irq;
	UINT8 m_dma;
	UINT16 m_dmalen;
	UINT32 m_readmsf;
	UINT32 m_readcount;
	bool m_locked;
	int m_drvmode;
	int m_curtoctrk;
	enum {
		STAT_CMD_CHECK = 0x01,
		STAT_PLAY_CDDA = 0x02,
		STAT_ERROR = 0x04,
		STAT_DISK_CDDA = 0x08,
		STAT_SPIN = 0x10,
		STAT_CHANGE = 0x20,
		STAT_READY = 0x40,
		STAT_OPEN = 0x80
	};
	enum {
		CMD_GET_INFO = 0x10,
		CMD_GET_Q = 0x20,
		CMD_GET_STAT = 0x40,
		CMD_SET_MODE = 0x50,
		CMD_SOFT_RESET = 0x60,
		CMD_STOPCDDA = 0x70,
		CMD_CONFIG = 0x90,
		CMD_SET_VOL = 0xae,
		CMD_READ1X = 0xc0,
		CMD_READ2X = 0xc1,
		CMD_GET_VER = 0xdc,
		CMD_STOP = 0xf0,
		CMD_EJECT = 0xf6,
		CMD_LOCK = 0xfe
	};
	enum {
		MODE_MUTE = 0x01,
		MODE_GET_TOC = 0x04,
		MODE_STOP = 0x08,
		MODE_ECC = 0x20,
		MODE_DATA = 0x40
	};
	enum {
		DRV_MODE_STOP,
		DRV_MODE_READ,
		DRV_MODE_CDDA
	};
	enum {
		FLAG_NODATA = 2,
		FLAG_NOSTAT = 4,
		FLAG_UNK = 8, //??
		FLAG_OPEN = 16
	};
	enum {
		IRQ_DATAREADY = 1,
		IRQ_DATACOMP = 2,
		IRQ_ERROR = 4
	};
};


// device type definition
extern const device_type ISA16_MCD;

#endif
