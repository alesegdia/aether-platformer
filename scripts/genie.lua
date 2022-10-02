AETHER_DIR = path.getabsolute("../module/aether")

dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "aether-platformer"
	startproject("jojo")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	language "C++"

	aetherBuild()

	aetherProject("jojo")
		includedirs {
			"../src/",
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h",
			"../gamesrc/jojo/**.cpp",
			"../gamesrc/jojo/**.h",
		}

	aetherProject("cortex")
		includedirs {
			"../src/",
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../src/**.cpp",
			"../src/**.h",
			"../gamesrc/cortex/**.cpp",
			"../gamesrc/cortex/**.h",
		}

dofile(path.join(AETHER_DIR, "scripts/tests/aether-tests.lua"))