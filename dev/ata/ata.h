#pragma once

#define SECTSIZE 512

#define ATA_READ 0x20
#define ATA_WRITE 0x30

#define ATA_MASTER 0
#define ATA_SLAVE 1

typedef unsigned lba_t;

void ata_rwsects(int drv_slave, int rwtype,
		void *buf, lba_t lba, unsigned count);
