-- Invokes build_*.lua in this directory and any sub directory
local isWindows = (package.config:sub(1,1) == '\\');
SLASH = "/";
if (isWindows) then SLASH = "\\"; end

function getDirectories(dir)
	local t = {};
	if (isWindows) then
		local pfile = io.popen('dir "'..dir..'" /b /ad');
		for f in pfile:lines() do
			t[#t+1] = f;
		end
	else
		local pfile = io.popen('ls -d "'..dir..'"/*/')
		for f in pfile:lines() do
			f = f:sub(dir:len()+2);
			f = f:sub(1, f:len()-1);
			t[#t+1] = f;
		end
 	end
 	return t;
end
 
function getFiles(dir)
	-- Returns the files AND directories in a specified directory
	local t = {};
	if (isWindows) then
		local pfile = io.popen('dir "'..dir..'" /b');
		for f in pfile:lines() do
			t[#t+1] = f;
		end
	else
		local pfile = io.popen('ls -a "'..dir..'"')
		for f in pfile:lines() do
			t[#t+1] = f;
		end
 	end
 	return t;
end

function doBuild(path, file)
	-- Test that file is a .lua file
	if (file:len() < 6) then return; end
	-- Test for build_*.lua
	if (not (file:sub(file:len() - 3) == ".lua")) then return; end
	if (not (file:sub(1,6) == "build_")) then return; end
	-- Prevent infinite loop
	if (file == "build_all.lua") then return; end
	-- Invoke
	print ("build_all.lua building: ", path..SLASH..file);
	local bf = loadfile(path..SLASH..file);
	INPUT_PREFIX = path..SLASH;
	bf(arg[1], arg[2], arg[3]);
end

function processDirectory(dir)
print("Processing Directory ", dir)
	local dirs = getDirectories(dir);
	local files = getFiles(dir);

	for i=1,#dirs do
		--print ("Dir: ", dirs[i])
	end
	for i=1,#files do
		--print ("File: ", files[i])
		doBuild (dir, files[i])
	end
	
	for i=1,#dirs do
		processDirectory(dir..SLASH..dirs[i]);
	end
end

processDirectory(".");

