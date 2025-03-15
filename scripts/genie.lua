dofile("../aether-config.lua")
dofile(path.join(AETHER_DIR, "scripts/util/util.lua"))

aetherConfig()

solution "aether-platformer"
	startproject("enerjim")
	location "../build/"
	configurations { "debug", "release" }
	platforms { "x32", "x64" }
	language "C++"
	
	aetherBuild()

	group("games")
	aetherProject("jojo")
		includedirs {
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../gamesrc/jojo/**.cpp",
			"../gamesrc/jojo/**.h",
			-- path.join(AETHER_DIR, "src/main/main.cpp")
		}

		aetherProject("enerjim")
		includedirs {
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../gamesrc/enerjim/**.cpp",
			"../gamesrc/enerjim/**.h",
			-- path.join(AETHER_DIR, "src/main/main.cpp")
	}

	aetherProject("demux")
		includedirs {
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../gamesrc/demux/**.cpp",
			"../gamesrc/demux/**.h",
		}

		--[[
	aetherProject("cortex")
		includedirs {
			"../gamesrc/"
		}
		debugdir ("..")
		targetdir ("../build")
		files {
			"../gamesrc/cortex/**.cpp",
			"../gamesrc/cortex/**.h",
			-- path.join(AETHER_DIR, "src/main/main.cpp")
		}
]]--

