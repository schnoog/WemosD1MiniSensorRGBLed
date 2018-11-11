from SCons.Script import DefaultEnvironment
import glob, shutil, os

env = DefaultEnvironment()
# uncomment line below to see environment variables
# print env.Dump()
# print ARGUMENTS

if not os.path.exists("lib/CMMC_OTA"):
    os.makedirs("lib/CMMC_OTA")

for file in glob.iglob('src/*.*'):
    print 'Copied %s' % (file)
    shutil.copy2(file, "lib/CMMC_OTA")
