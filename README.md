# MikanOS
**「ゼロからのOS自作入門」** をやっていく  
1日1章を目標に  

<br>

# Kernel Compile and Link
```
$ cd /workspaces/MikanOS-devcontainer/mikanos/kernel
$ clang++ $CPPFLAGS -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone -fno-exceptions -fno-rtti -std=c++17 -c main.cpp
$ ld.lld $LDFLAGS --entry KernelMain -z norelro --image-base 0x100000 --static -o kernel.elf main.o  
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
$ $HOME/osbook/devenv/run_qemu.sh $HOME/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi /workspaces/MikanOS-devcontainer/mikanos/kernel/kernel.elf
```
