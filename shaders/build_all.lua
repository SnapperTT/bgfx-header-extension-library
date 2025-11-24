-- Invokes build_*.lua in this directory and any sub directory
-- Usage: lua build_all.lua (singlethreaded)
--
--        lua build_all.lua 1 4 &\
--        lua build_all.lua 2 4 &\
--        lua build_all.lua 3 4 &\
--        lua build_all.lua 4 4 (multithreaded with 4 threads)

local isWindows = (package.config:sub(1,1) == '\\');
SLASH = "/";
if (isWindows) then SLASH = "\\"; end

-- Parse multithreaded build
INSTANCE_ID = 0
NUM_INSTANCES = 0
numberCount = 0

local newArg = {}
local numberCount = 0

for i=1,#arg do
	local n = tonumber(arg[i])
	if (n) then
		numberCount = numberCount + 1
		if (numberCount == 1) then
			INSTANCE_ID = n
		elseif (numberCount == 2) then
			NUM_INSTANCES = n
		end
    else
        table.insert(newArg, a)
	end
end

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

function isBuildScript(path, file)
	-- Test that file is a .lua file
	if (file:len() < 6) then return false; end
	-- Test for build_*.lua
	if (not (file:sub(file:len() - 3) == ".lua")) then return false; end
	if (not (file:sub(1,6) == "build_")) then return false; end
	-- Prevent infinite loop
	if (file == "build_all.lua") then return false; end
	return true;
end

function doBuild(path, file)
	-- Invoke
	if (not isBuildScript(path, file)) then return; end
	--print ("build_all.lua building: ", path..SLASH..file);
	local bf = loadfile(path..SLASH..file);
	INPUT_PREFIX = path..SLASH;
	if (INSTANCE_ID) then
		bf("-THREAD_ID", INSTANCE_ID, table.unpack(newArg));
	else
		bf(table.unpack(newArg));
	end
end

function processDirectory(dir)
	-- Process a directory to get a file list
	--print("Processing Directory ", dir)
	local dirs = getDirectories(dir);
	local files = getFiles(dir);

	for i=1,#dirs do
		--print ("Dir: ", dirs[i])
	end
	for i=1,#files do
		--print ("File: ", files[i])
		if (isBuildScript(dir, files[i])) then
			FILE_LIST[#FILE_LIST+1] = { dir, files[i] }
		end
	end
	
	for i=1,#dirs do
		processDirectory(dir..SLASH..dirs[i]);
	end
	--print("Completed Processing Directory ", dir)
end

FILE_LIST = {}
processDirectory(".");

print ("Scripts to build:")
for i = 1,#FILE_LIST do
	print(FILE_LIST[i][1], FILE_LIST[i][2]);
end
for i = 1,#FILE_LIST do
    if ((NUM_INSTANCES > 1) and (INSTANCE_ID > 0)) then
        -- Check if this iteration belongs to this instance
        if (((i - 1) % NUM_INSTANCES) ~= (INSTANCE_ID - 1)) then
			--print ("SKIPPING ", i, " thread ", INSTANCE_ID, " of " .. NUM_INSTANCES)
            goto continue
        end
    end
	--print ("BUILDING ", i, " thread ", INSTANCE_ID, " of " .. NUM_INSTANCES .. " " .. FILE_LIST[i][2])
	doBuild(FILE_LIST[i][1], FILE_LIST[i][2])
	::continue::
end

