rm $1.bin
rm 1ST_READ.bin
rm $1.ISO
rm $1.CDI

sh-elf-objcopy -R .stack -O binary $1.elf $1.bin
$KOS_HOME/utils/scramble/scramble $1.bin 1ST_READ.bin
currDir=$(pwd)

mkisofs -C 0,11702 -V DREAMGAME -G IP.BIN -joliet -rock -l -o $1.ISO $currDir
cdi4dc $1.ISO $1.CDI
