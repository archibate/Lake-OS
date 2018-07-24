; vim: ft=nasm ai

global _initrd
global initrd_apps
global end_initrd_apps

initrd_apps:
	dd _a0
	dd _a1
	dd _a2
	dd _a3
	dd _a4
	dd _a5
	dd _a6
end_initrd_apps:

_initrd:
_a0:
incbin "../usr/wtest/bin/wtest.com"
_a1:
incbin "../usr/mtest/bin/mtest.com"
_a2:
incbin "../dev/zero/bin/zero.com"
_a3:
incbin "../dev/rand/bin/rand.com"
_a4:
incbin "../dev/fd0/bin/fd0.com"
_a5:
incbin "../dev/ata/bin/ata.com"
_a6:
