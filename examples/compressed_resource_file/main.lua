-- Simple example to store compressed image to file. 
-- To store multiple assets, some sort of addressing would be required.

package.path = package.path..";"..RL.GetBasePath().."../resources/lib/?.lua"

Vector2 = require( "vector2" )

local texture = nil
local dataFileName = "data"
local compress = true
-- local compress = false

local function writeDataFile( path )
	local image = RL.LoadImage( RL.GetBasePath().."../resources/images/arcade_platformerV2.png" )

	if not image then
		return
	end

	local imgData = {
		size = Vector2:newT( RL.GetImageSize( image ) ),
		mipmaps = RL.GetImageMipmaps( image ),
		format = RL.GetImageFormat( image ),
		data = RL.GetImageData( image ),
	}
	-- Header and image data. We devide imgData.data by 4 since we use unsigned ints as buffer type.
	local totalLength = 4 + RL.GetBufferLength( imgData.data ) / 4
	local buffer = RL.LoadBufferFormatted( totalLength, RL.BUFFER_UNSIGNED_INT, 0 )

	RL.SetBufferData( buffer, 0, {
		imgData.size.x,
		imgData.size.y,
		imgData.mipmaps,
		imgData.format,
	} )
	RL.CopyBufferData( buffer, imgData.data, 4, 0, RL.GetBufferLength( imgData.data ) )

	if compress then
		RL.ExportBuffer( RL.CompressData( buffer ), path )
	else
		RL.ExportBuffer( buffer, path )
	end
end

local function loadDataFile( path )
	local buffer = RL.LoadBufferFromFile( path, RL.BUFFER_UNSIGNED_INT )

	if not buffer then
		return
	end
	
	if compress then
		buffer = RL.DecompressData( buffer )
	end

	local imgData = {
		size = Vector2:newT( RL.GetBufferData( buffer, 0, 2 ) ),
		mipmaps = RL.GetBufferData( buffer, 2, 1 )[1],
		format = RL.GetBufferData( buffer, 3, 1 )[1],
		data = nil,
	}
	local imageDataSize = RL.GetPixelDataSize( imgData.size, imgData.format )

	imgData.data = RL.LoadBufferFormatted( imageDataSize, RL.BUFFER_UNSIGNED_CHAR, 0 )

	RL.CopyBufferData( imgData.data, buffer, 0, 4, imageDataSize )

	local image = RL.LoadImageFromData(
		imgData.data,
		imgData.size,
		imgData.mipmaps,
		imgData.format
	)
	texture = RL.LoadTextureFromImage( image )
end

function RL.init()
	RL.SetWindowTitle( "Compressed resource file" )
	RL.SetWindowState( RL.FLAG_VSYNC_HINT )

	local path = RL.GetBasePath()..dataFileName

	writeDataFile( path )
	loadDataFile( path )
end

function RL.update( delta )
end

function RL.draw()
	RL.ClearBackground( RL.RAYWHITE )

	if texture then
		RL.DrawTextureEx( texture, { 0, 0 }, 0, 2, RL.WHITE )
	end
end
