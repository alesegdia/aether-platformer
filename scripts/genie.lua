dofile("../aether-config.lua")
dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "aether-platformer"
	startproject("jojo")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	language "C++"
	
	aetherBuild()

	group("games")
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
			-- path.join(AETHER_DIR, "src/main/main.cpp")
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
			-- path.join(AETHER_DIR, "src/main/main.cpp")
		}

