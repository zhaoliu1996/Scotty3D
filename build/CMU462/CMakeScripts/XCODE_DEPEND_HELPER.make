# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.glew.Debug:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/Debug/libglew.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/Debug/libglew.a


PostBuild.glfw.Debug:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/Debug/libglfw3.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/Debug/libglfw3.a


PostBuild.CMU462.Debug:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/src/Debug/libCMU462.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/src/Debug/libCMU462.a


PostBuild.glew.Release:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/Release/libglew.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/Release/libglew.a


PostBuild.glfw.Release:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/Release/libglfw3.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/Release/libglfw3.a


PostBuild.CMU462.Release:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/src/Release/libCMU462.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/src/Release/libCMU462.a


PostBuild.glew.MinSizeRel:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/MinSizeRel/libglew.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/MinSizeRel/libglew.a


PostBuild.glfw.MinSizeRel:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/MinSizeRel/libglfw3.a


PostBuild.CMU462.MinSizeRel:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/src/MinSizeRel/libCMU462.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/src/MinSizeRel/libCMU462.a


PostBuild.glew.RelWithDebInfo:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/RelWithDebInfo/libglew.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glew/RelWithDebInfo/libglew.a


PostBuild.glfw.RelWithDebInfo:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/deps/glfw/src/RelWithDebInfo/libglfw3.a


PostBuild.CMU462.RelWithDebInfo:
/Users/liuzhao/Repository/Scotty3D/build/CMU462/src/RelWithDebInfo/libCMU462.a:
	/bin/rm -f /Users/liuzhao/Repository/Scotty3D/build/CMU462/src/RelWithDebInfo/libCMU462.a




# For each target create a dummy ruleso the target does not have to exist
