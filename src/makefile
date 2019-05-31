# This makefile creates the .h files in the parent directory from .lzz files here
LAZY=../tools/lzz -hx hh
RAWSOURCES=bgfxh.lzz bgfxh_embedded_shader.lzz bloomFilter.lzz cascadingShadowMapFilter.lzz loadTexture.lzz lumFilter.lzz sdlWindow.lzz tonemappingFilter.lzz
OUTPUTDIR=../
TEMPDIR=temp/
SOURCES=$(addprefix $(TEMPDIR),$(RAWSOURCES:.lzz=.cpp))
SFI=$(addprefix $(OUTPUTDIR), $(RAWSOURCES:.lzz=.h))

all: $(SOURCES) $(SFI)

.PHONEY clean:
	rm -rf $(TEMPDIR)*

# Convert .lzz to .cpp and .hh
$(TEMPDIR)%.cpp $(TEMPDIR)%.hh: %.lzz
	$(LAZY) -o $(TEMPDIR) $<
	
# Concatenate the .cpp and .hh files into a single header
# and enable the BGFX_IMPL macro
# then remove any instance of #include "filename.hh" that
# lzz has added
$(OUTPUTDIR)%.h: $(TEMPDIR)%.cpp $(TEMPDIR)%.hh
	cat $(TEMPDIR)$*.hh > $@
	echo '' >> $@
	echo '////////////////////////////////////////////////////////////////////////' >> $@
	echo '' >> $@
	echo '#ifdef BGFXH_IMPL' >> $@
	cat $(TEMPDIR)$*.cpp >> $@
	echo '#endif //BGFXH_IMPL' >> $@
	sed -i '/#include ".*\.hh"/d' $@ 
	
