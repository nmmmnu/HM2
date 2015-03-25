Prior the test you need to generate data files

Link list, Vector and Skip list will generate correct file.

mkdir test_glob/data.bin

./test_hm_disktable make test_glob/data.001.txt test_glob/data.bin/bin.001
./test_hm_disktable make test_glob/data.002.txt test_glob/data.bin/bin.002
./test_hm_disktable make test_glob/data.003.txt test_glob/data.bin/bin.003

Then you can do:

./test_hm_dir find './test_glob/data.bin/bin.*' Bonn
./test_hm_dir find './test_glob/data.bin/bin.*' Sofia

./test_hm_dir dump './test_glob/data.bin/bin.*'

