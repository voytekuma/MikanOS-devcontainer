# MikanOS
**「ゼロからのOS自作入門」** をやっていく  
1日1章を目標に  

<br>

# Kernel Compile and Link
```
$ cd $MIKAN/kernel
$ make 
```
 
<br>

# Build BootLoader
```
$ cd $HOME/edk2
$ source edksetup.sh
$ build
```

<br>

# Run QEMU
```
$ $HOME/osbook/devenv/run_qemu.sh $HOME/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi $MIKAN/kernel/kernel.elf
```
