import os
import ycm_core

HOME = os.environ['HOME']
TOOLCHAIN_PATH = \
    '/home/portia_labiata/.platformio/packages/toolchain-gccarmnoneeabi/'

flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-x', 'c++',
    '--std=c++11',
    '-nostdinc',
    '-Os',
    f'--gcc-toolchain={TOOLCHAIN_PATH}',
]

system_includes = [
    'arm-none-eabi/include',
    'arm-none-eabi/include/c++/7.2.1',
    'arm-none-eabi/include/c++/7.2.1/arm-none-eabi',
    'arm-none-eabi/include/c++/7.2.1/backward',
    'lib/gcc/arm-none-eabi/7.2.1/include',
    'lib/gcc/arm-none-eabi/7.2.1/include-fixed',
]

include_dirs = [
    '/home/portia_labiata/.platformio/packages/framework-spl/stm32/spl/variants/stm32f4/inc',
    '/home/portia_labiata/.platformio/packages/framework-spl/stm32/cmsis/cores/stm32',
    '/home/portia_labiata/.platformio/packages/framework-spl/stm32/cmsis/variants/stm32f4',
    '/home/portia_labiata/.platformio/packages/framework-cmsis-stm32f4/Include/',
    'include',
]

recurse_dirs = [
    'lib',
    '/home/portia_labiata/.platformio/packages/framework-spl',
]

defines = [
]


def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))


def helper_make_includes(dirs):
    result = []
    for d in dirs:
        abs_path = d
        if not os.path.isabs(d):
            abs_path = os.path.join(DirectoryOfThisScript(), d)
        result.extend(['-I', abs_path])
    return result


def helper_include_subdirs(parents):
    result = []
    for parent in parents:
        for root, dirs, _ in os.walk(parent):
            root = os.path.join(DirectoryOfThisScript(), root)
            result.extend(['-I', root])
    return result


def helper_make_defines(defs):
    result = []
    for define in defs:
        result.append(f'-D{define}')
    return result


def helper_make_system_paths(paths):
    result = []
    for path in paths:
        result.extend(['-I', os.path.join(TOOLCHAIN_PATH, path)])
    return result


flags += helper_make_system_paths(system_includes) + \
    helper_make_defines(defines) + \
    helper_make_includes(include_dirs) + \
    helper_include_subdirs(recurse_dirs)


def Settings(**kwargs):
    lang = kwargs['language']
    if lang == 'cfamily':
        return {
            'flags': flags,
            'include_paths_relative_to_dir': DirectoryOfThisScript(),
        }
    elif lang == 'python':
        return {
            'interpreter_path': '/home/portia_labiata/anaconda3/bin/python',
        }
    return {}

def FlagsForFile(filename):
    return flags
