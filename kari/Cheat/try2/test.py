import re

fw = open("data","rw")
Str = fw.read()
fw.close()

rule="(\/\*(\s|.)*?\*\/)|(\/\/.*)"
#re_comment = re.compile()
Str = re.sub(rule,"",Str)
print Str

fw = open("data","w")
fw.write(Str)
fw.close()
