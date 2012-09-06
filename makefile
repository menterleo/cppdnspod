object = httphandle.h httphandle.cc cppdnspod.cc
dnspod : $(object)
	g++ $(object) -lcurl -o cppdnspod

run :
	./cppdnspod

