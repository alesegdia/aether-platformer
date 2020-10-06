AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "aether-platformer"
	startproject("platformer-game")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	language "C++"
	
	aetherBuild()

	aetherProject("platformer-game")
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h"
		}

