#include <asm.h>
#include <clicrit.h>
#include <assert.h>
#include "ata.h"

#define ATA_CRIT_BEGIN(n)
#define ATA_CRIT_END(n)

static void waitdisk(void)
{
	while ((io_inb(0x1f7) & 0xc0) != 0x40);
}

static void ata_cmd_out(int drv_slave, int rwtype,
		lba_t lba, unsigned count)
{
	CLI_CRIT_BEGIN(1);
	io_outb(0x1F2, count);
	io_outb(0x1f3, lba);
	io_outb(0x1f4, lba >> 8);
	io_outb(0x1f5, lba >> 16);
	unsigned char dev = lba >> 24;
	dev |= drv_slave ? 0xf0 : 0xe0;
	io_outb(0x1f6, dev);
	io_outb(0x1f7, rwtype);
	CLI_CRIT_END(1);
}

static void ata_data_in(void *buf, unsigned count)
{
	CLI_CRIT_BEGIN(1);
	io_insl(0x1f0, buf, count * SECTSIZE/4);
	CLI_CRIT_END(1);
}

static void ata_data_out(const void *buf, unsigned count)
{
	CLI_CRIT_BEGIN(1);
	io_outsl(0x1f0, buf, count * SECTSIZE/4);
	CLI_CRIT_END(1);
}

void ata_rwsects(int drv_slave, int rwtype,
		void *buf, lba_t lba, unsigned count)
{
	ATA_CRIT_BEGIN(1);
	ata_cmd_out(drv_slave, rwtype, lba, count);
	waitdisk();
	if (rwtype == ATA_READ) {
		ata_data_in(buf, count);
	} else if (rwtype == ATA_WRITE) {
		ata_data_out(buf, count);
	} else {
		assert(0);
	}
	ATA_CRIT_END(1);
}
