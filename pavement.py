import errno
import os
from paver.easy import *
import shutil

build_dir = 'build'

kernel_source_dir = 'kernel'
kernel_c_sources = [item for item in os.listdir(kernel_source_dir) if item.endswith('.c') and not os.path.isdir(item)]
kernel_asm_sources = [item for item in os.listdir(kernel_source_dir) if item.endswith('.asm') and not os.path.isdir(item)]
kernel_out_dir = os.path.join(build_dir, 'kernel')

libc_source_dir = 'libc'
libc_out_dir = os.path.join(build_dir, 'libc')
libc_host_out_dir = os.path.join(build_dir, 'libc_host')
libc_source_files = [item for item in os.listdir(libc_source_dir) if item.endswith('.c') and not os.path.isdir(item)]
libc_compile_command_format = '{cc} -std=gnu99 -ffreestanding -O2 -nostdlib -Wall -Wextra -Ilibc/include -Ikernel/include -c {src_file} -o {out}'
libc_make_lib_commmand_format = '{ar} rcs {out} {object_files}'

def require_dir(path):
    try:
        os.stat(path)
    except OSError, e:
        if e.errno == errno.ENOENT:
            os.makedirs(path)

@task
def clean():
    shutil.rmtree(build_dir)

@task
@needs('kernel')
def iso():
    require_dir(os.path.join(build_dir, 'iso', 'boot', 'grub'))
    shutil.copyfile(os.path.join(build_dir, 'norby.bin'), os.path.join(build_dir, 'iso', 'boot', 'norby.bin'))
    shutil.copyfile(os.path.join('grub', 'grub.cfg'), os.path.join(build_dir, 'iso', 'boot', 'grub', 'grub.cfg'))
    sh('grub-mkrescue -o {0} {1}'.format(os.path.join(build_dir, 'norby.iso'), os.path.join(build_dir, 'iso')))

@task
@needs(['libc'])
def kernel():
    require_dir(kernel_out_dir)
    object_files = []
    for asm_source_file in kernel_asm_sources:
        asm_source_file_full = os.path.join(kernel_source_dir, asm_source_file)
        out = os.path.join(kernel_out_dir, asm_source_file + '.o')
        sh('nasm -felf32 {source_file} -o {out} -i{include}/'.format(source_file=asm_source_file_full, out=out, include=os.path.join(kernel_source_dir, 'asm')))
        object_files.append(out)
    for c_source_file in kernel_c_sources:
        c_source_file_full = os.path.join(kernel_source_dir, c_source_file)
        out = os.path.join(kernel_out_dir, c_source_file + '.o')
        sh('i686-elf-gcc -std=gnu99 -ffreestanding -O2 -nostdlib -Wall -Wextra -Ilibc/include -Lbuild/libc -lnorbyc -Ikernel/include -c {0} -o {1}'.format(c_source_file_full, os.path.join(kernel_out_dir, c_source_file + '.o')))
        object_files.append(out)
    object_files_string = ' '.join(object_files)
    sh('i686-elf-gcc -T {kernel_src_dir}/linker.ld -o {build_dir}/norby.bin -std=gnu99 -ffreestanding -O2 -nostdlib -Wall -Wextra {objs} -Lbuild/libc -lnorbyc'.format(kernel_src_dir=kernel_source_dir, build_dir=build_dir, objs=object_files_string))

@task
@cmdopts([('for_host', 'f', 'Build for host or use cross-compiler')])
def libc(options):
    build_for_host = 'for_host' in options.libc.keys()
    out_dir = libc_host_out_dir if build_for_host else libc_out_dir
    cc = 'gcc' if build_for_host else 'i686-elf-gcc'
    ar = 'ar' if build_for_host else 'i686-elf-ar'
    object_files = []
    require_dir(out_dir)
    for source_file in libc_source_files:
        relative_path = os.path.join(libc_source_dir, source_file)
        out = os.path.join(out_dir, source_file + '.o')
        object_files.append(out)
        command = libc_compile_command_format.format(cc=cc, src_file=relative_path, out=out)
        sh(command)
    sh(libc_make_lib_commmand_format.format(ar=ar, out=os.path.join(out_dir, 'libnorbyc.a'), object_files=' '.join(object_files)))

@task
@needs(['kernel'])
def run():
    sh('qemu-system-i386 -kernel {}/norby.bin'.format(build_dir))

@task
@needs(['iso'])
def run_iso():
    sh('qemu-system-i386 {iso_loc}'.format(iso_loc=os.path.join(build_dir, 'norby.iso')))

@task
def test_libc():
    sh('paver libc --for_host') #I can't figure out a way to @needs it with the flag
    sh('cd libc/tests && python3 run_tests.py')
