/*
  NAME: bmp2arry.ex
  DESCRIPTION: convert monochrome bitmap to C array.
  USAGE: bmp2array.ex  input.bmp output.c
*/

include "std/io.e"
include "std/sequence.e"
include "std/text.e"

sequence input_file, output_file

procedure usage()
    puts(1,"USAGE: bmp2array.ex input.bmp output.c\n")
    abort(0)
end procedure

procedure parse_cmd_line()
sequence argv
integer argc
    argv=command_line()
    argc=length(argv)
    if argc<4 then usage() end if
    input_file=argv[3]
    output_file=argv[4]
end procedure

function read_int16(integer fh)
    return getc(fh)+256*getc(fh)
end function

function read_int32(integer fh)
    return getc(fh)+256*getc(fh)+65536*getc(fh)+256*65536*getc(fh)
end function

function read_bmp_header(integer fh)
sequence field, bmp_fmt
   bmp_fmt={}
   field=getc(fh) & getc(fh)
   if not equal(field,"BM") then
      puts(1,"not a bitmap file\n")
      abort(0)
   end if
   bmp_fmt &= read_int32(fh) -- file size
   read_int32(fh) -- skip this
   bmp_fmt &= read_int32(fh) -- offset to data
   bmp_fmt &= read_int32(fh) -- DIB header size
   bmp_fmt &= read_int32(fh) -- image width in pixels
   bmp_fmt &= read_int32(fh) -- image height in pixels
   bmp_fmt &= read_int16(fh) -- number of colors plane should be 1
   bmp_fmt &= read_int16(fh) -- number of bits per pixel
   bmp_fmt &= read_int32(fh) -- compression mode should be 0
   bmp_fmt &= read_int32(fh) -- raw image size
   bmp_fmt &= read_int32(fh) -- horizontal resolution bits per meter
   bmp_fmt &= read_int32(fh) -- vertical resolution bits per meter
   bmp_fmt &= read_int32(fh) -- number of color in palette
   bmp_fmt &= read_int32(fh) -- number of important color in palette
   return bmp_fmt
end function

procedure create_header_file(sequence bmp_fmt)
sequence header_name
integer fo,array_width

   header_name=output_file[1..$-1]&'h'
   fo = open(header_name,"wb")
   if fo=-1 then 
       printf(1,"Failed to create header file %s\n",header_name)
       abort(0)
   end if
   array_width=floor(bmp_fmt[4]/8)
   if remainder(bmp_fmt[4],8)>0 then array_width+=1 end if
   printf(fo,"#ifndef _%s\n",{upper(header_name[1..$-2])})
   printf(fo,"#define _%s\n\n",{upper(header_name[1..$-2])})
   printf(fo,"#define ARRAY_WIDTH %d\n",array_width)
   printf(fo,"#define PIX_WIDTH %d\n",bmp_fmt[4])
   printf(fo,"#define PIX_HEIGHT %d\n", bmp_fmt[5])
   printf(fo,"\nextern const unsigned char %s[PIX_HEIGHT][ARRAY_WIDTH];\n",{upper(header_name[1..$-2])})
   printf(fo,"\n#endif // _%s\n",{upper(header_name[1..$-2])})
   close(fo)
end procedure

function read_bmp_data(sequence bmp_fmt, integer fh)
integer width, height, byte_per_line
sequence line, bmp

   seek(fh,bmp_fmt[2])
   bmp={}
   width=bmp_fmt[4]
   height=bmp_fmt[5]
   byte_per_line=floor(width/8)
   if remainder(width,8)>0 then byte_per_line += 1 end if
   for l=1 to height do
       line={}
       for r=1 to byte_per_line do
           line &= getc(fh)
       end for
       bmp = append(bmp,line)
   end for
   return bmp
end function


procedure convert_bmp(sequence bmp_fmt,integer fh)
sequence data, array_name
integer fo

   printf(1,"\nbitmap size: width %d, height %d pixels.\n",bmp_fmt[4..5])
   data = read_bmp_data(bmp_fmt,fh)
   if length(output_file) then
       fo= open(output_file,"wb")
       if fo=-1 then
           printf(1,"Failed to open %s\n",output_file)
           abort(0)
       end if
       create_header_file(bmp_fmt)
       array_name=upper(output_file[1..$-2])
       puts(fo,"// monochrome bitmap data\n\n")
       printf(fo,"#include \"%s\"\n\n",{output_file[1..$-1]&'h'})
       printf(fo,"const unsigned char %s[PIX_HEIGHT][ARRAY_WIDTH]={\n",{array_name})
       for l=length(data) to 1 by -1 do
           puts(fo,"{")
           for r=1 to length(data[l]) do
               if r<length(data[l]) then
                   printf(fo,"0x%02x, ",data[l][r])
               else
                   printf(fo,"0x%02x},\n",data[l][r])
               end if
           end for
       end for
       puts(fo,"};\n")
       close(fo)
   else
       puts(1,"no output file\n")    
   end if 
end procedure



procedure main()
sequence bmp_fmt
integer fh
   parse_cmd_line()
   if length(input_file) then
      fh=open(input_file,"rb")
      if fh=-1 then 
          printf(1,"failed to open %s\n",input_file)  
          abort(0) 
      end if
      bmp_fmt=read_bmp_header(fh)
      convert_bmp(bmp_fmt,fh)
      close(fh)
   else
       puts(1,"no input file\n")
   end if
end procedure

main()
