desc: --time-unit=B
cmd: ./test_hm_file_ha data/ru_domains.shuffle.30K.txt NIC.RU
time_unit: B
#-----------
snapshot=0
#-----------
time=0
mem_heap_B=0
mem_heap_extra_B=0
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=1
#-----------
time=24
mem_heap_B=16
mem_heap_extra_B=8
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=2
#-----------
time=33558496
mem_heap_B=33554448
mem_heap_extra_B=4048
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=3
#-----------
time=34828872
mem_heap_B=34798388
mem_heap_extra_B=30484
mem_stacks_B=0
heap_tree=detailed
n3: 34798388 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 1175552 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 1175552 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 1175552 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 1175552 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 1175552 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 1175552 0x400ABB: processfile (test_hm_file.c:78)
       n0: 1175552 0x40099B: main (test_hm_file.c:27)
 n0: 68404 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=4
#-----------
time=35935864
mem_heap_B=35882074
mem_heap_extra_B=53790
mem_stacks_B=0
heap_tree=detailed
n3: 35882074 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 2199552 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 2199552 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 2199552 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 2199552 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 2199552 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 2199552 0x400ABB: processfile (test_hm_file.c:78)
       n0: 2199552 0x40099B: main (test_hm_file.c:27)
 n0: 128090 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=5
#-----------
time=36763720
mem_heap_B=36692760
mem_heap_extra_B=70960
mem_stacks_B=0
heap_tree=detailed
n3: 36692760 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 2965504 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 2965504 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 2965504 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 2965504 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 2965504 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 2965504 0x400ABB: processfile (test_hm_file.c:78)
       n0: 2965504 0x40099B: main (test_hm_file.c:27)
 n0: 172824 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=6
#-----------
time=38227960
mem_heap_B=38126440
mem_heap_extra_B=101520
mem_stacks_B=0
heap_tree=detailed
n3: 38126440 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 4320256 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 4320256 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 4320256 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 4320256 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 4320256 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 4320256 0x400ABB: processfile (test_hm_file.c:78)
       n0: 4320256 0x40099B: main (test_hm_file.c:27)
 n0: 251752 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=7
#-----------
time=39303864
mem_heap_B=39179964
mem_heap_extra_B=123900
mem_stacks_B=0
heap_tree=detailed
n3: 39179964 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 5315584 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 5315584 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 5315584 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 5315584 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 5315584 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 5315584 0x400ABB: processfile (test_hm_file.c:78)
       n0: 5315584 0x40099B: main (test_hm_file.c:27)
 n0: 309948 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=8
#-----------
time=40740184
mem_heap_B=40586108
mem_heap_extra_B=154076
mem_stacks_B=0
heap_tree=detailed
n3: 40586108 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 6644736 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 6644736 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 6644736 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 6644736 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 6644736 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 6644736 0x400ABB: processfile (test_hm_file.c:78)
       n0: 6644736 0x40099B: main (test_hm_file.c:27)
 n0: 386940 in 3 places, all below massif's threshold (01.00%)
#-----------
snapshot=9
#-----------
time=41733016
mem_heap_B=41558008
mem_heap_extra_B=175008
mem_stacks_B=0
heap_tree=detailed
n4: 41558008 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 7563264 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 7563264 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 7563264 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 7563264 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 7563264 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 7563264 0x400ABB: processfile (test_hm_file.c:78)
       n0: 7563264 0x40099B: main (test_hm_file.c:27)
 n1: 439728 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 439728 0x400AA6: processfile (test_hm_file.c:78)
   n0: 439728 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=10
#-----------
time=42835112
mem_heap_B=42636964
mem_heap_extra_B=198148
mem_stacks_B=0
heap_tree=detailed
n4: 42636964 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 8583168 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 8583168 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 8583168 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 8583168 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 8583168 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 8583168 0x400ABB: processfile (test_hm_file.c:78)
       n0: 8583168 0x40099B: main (test_hm_file.c:27)
 n1: 498780 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 498780 0x400AA6: processfile (test_hm_file.c:78)
   n0: 498780 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=11
#-----------
time=44322360
mem_heap_B=44092984
mem_heap_extra_B=229376
mem_stacks_B=0
heap_tree=detailed
n4: 44092984 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 9958400 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 9958400 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 9958400 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 9958400 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 9958400 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 9958400 0x400ABB: processfile (test_hm_file.c:78)
       n0: 9958400 0x40099B: main (test_hm_file.c:27)
 n1: 579568 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 579568 0x400AA6: processfile (test_hm_file.c:78)
   n0: 579568 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=12
#-----------
time=45999272
mem_heap_B=45734594
mem_heap_extra_B=264678
mem_stacks_B=0
heap_tree=detailed
n4: 45734594 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 11508736 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 11508736 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 11508736 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 11508736 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 11508736 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 11508736 0x400ABB: processfile (test_hm_file.c:78)
       n0: 11508736 0x40099B: main (test_hm_file.c:27)
 n1: 670842 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 670842 0x400AA6: processfile (test_hm_file.c:78)
   n0: 670842 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=13
#-----------
time=47566984
mem_heap_B=47269486
mem_heap_extra_B=297498
mem_stacks_B=0
heap_tree=detailed
n4: 47269486 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 12958720 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 12958720 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 12958720 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 12958720 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 12958720 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 12958720 0x400ABB: processfile (test_hm_file.c:78)
       n0: 12958720 0x40099B: main (test_hm_file.c:27)
 n1: 755750 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 755750 0x400AA6: processfile (test_hm_file.c:78)
   n0: 755750 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=14
#-----------
time=49458744
mem_heap_B=49121282
mem_heap_extra_B=337462
mem_stacks_B=0
heap_tree=detailed
n4: 49121282 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 14707712 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 14707712 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 14707712 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 14707712 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 14707712 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 14707712 0x400ABB: processfile (test_hm_file.c:78)
       n0: 14707712 0x40099B: main (test_hm_file.c:27)
 n1: 858554 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 858554 0x400AA6: processfile (test_hm_file.c:78)
   n0: 858554 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=15
#-----------
time=50476456
mem_heap_B=50117486
mem_heap_extra_B=358970
mem_stacks_B=0
heap_tree=detailed
n4: 50117486 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 15648768 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 15648768 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 15648768 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 15648768 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 15648768 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 15648768 0x400ABB: processfile (test_hm_file.c:78)
       n0: 15648768 0x40099B: main (test_hm_file.c:27)
 n1: 913702 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 913702 0x400AA6: processfile (test_hm_file.c:78)
   n0: 913702 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=16
#-----------
time=51550360
mem_heap_B=51168724
mem_heap_extra_B=381636
mem_stacks_B=0
heap_tree=detailed
n4: 51168724 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 16642048 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 16642048 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 16642048 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 16642048 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 16642048 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 16642048 0x400ABB: processfile (test_hm_file.c:78)
       n0: 16642048 0x40099B: main (test_hm_file.c:27)
 n1: 971660 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 971660 0x400AA6: processfile (test_hm_file.c:78)
   n0: 971660 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=17
#-----------
time=52649160
mem_heap_B=52244154
mem_heap_extra_B=405006
mem_stacks_B=0
heap_tree=detailed
n4: 52244154 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 17657856 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 17657856 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 17657856 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 17657856 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 17657856 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 17657856 0x400ABB: processfile (test_hm_file.c:78)
       n0: 17657856 0x40099B: main (test_hm_file.c:27)
 n1: 1031282 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1031282 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1031282 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=18
#-----------
time=53857592
mem_heap_B=53427252
mem_heap_extra_B=430340
mem_stacks_B=0
heap_tree=detailed
n4: 53427252 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 18775040 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 18775040 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 18775040 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 18775040 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 18775040 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 18775040 0x400ABB: processfile (test_hm_file.c:78)
       n0: 18775040 0x40099B: main (test_hm_file.c:27)
 n1: 1097196 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1097196 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1097196 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=19
#-----------
time=55776776
mem_heap_B=55305926
mem_heap_extra_B=470850
mem_stacks_B=0
heap_tree=detailed
n4: 55305926 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 20548608 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 20548608 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 20548608 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 20548608 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 20548608 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 20548608 0x400ABB: processfile (test_hm_file.c:78)
       n0: 20548608 0x40099B: main (test_hm_file.c:27)
 n1: 1202302 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1202302 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1202302 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=20
#-----------
time=57090568
mem_heap_B=56591914
mem_heap_extra_B=498654
mem_stacks_B=0
heap_tree=detailed
n4: 56591914 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 21762048 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 21762048 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 21762048 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 21762048 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 21762048 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 21762048 0x400ABB: processfile (test_hm_file.c:78)
       n0: 21762048 0x40099B: main (test_hm_file.c:27)
 n1: 1274850 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1274850 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1274850 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=21
#-----------
time=58573704
mem_heap_B=58043710
mem_heap_extra_B=529994
mem_stacks_B=0
heap_tree=detailed
n4: 58043710 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 23133184 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 23133184 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 23133184 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 23133184 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 23133184 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 23133184 0x400ABB: processfile (test_hm_file.c:78)
       n0: 23133184 0x40099B: main (test_hm_file.c:27)
 n1: 1355510 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1355510 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1355510 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=22
#-----------
time=60164472
mem_heap_B=59600794
mem_heap_extra_B=563678
mem_stacks_B=0
heap_tree=detailed
n4: 59600794 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 24603648 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 24603648 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 24603648 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 24603648 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 24603648 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 24603648 0x400ABB: processfile (test_hm_file.c:78)
       n0: 24603648 0x40099B: main (test_hm_file.c:27)
 n1: 1442130 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1442130 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1442130 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=23
#-----------
time=61835016
mem_heap_B=61236266
mem_heap_extra_B=598750
mem_stacks_B=0
heap_tree=detailed
n4: 61236266 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 26147840 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 26147840 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 26147840 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 26147840 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 26147840 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 26147840 0x400ABB: processfile (test_hm_file.c:78)
       n0: 26147840 0x40099B: main (test_hm_file.c:27)
 n1: 1533410 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1533410 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1533410 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=24
#-----------
time=63691224
mem_heap_B=63053254
mem_heap_extra_B=637970
mem_stacks_B=0
heap_tree=detailed
n4: 63053254 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 27863040 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 27863040 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 27863040 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 27863040 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 27863040 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 27863040 0x400ABB: processfile (test_hm_file.c:78)
       n0: 27863040 0x40099B: main (test_hm_file.c:27)
 n1: 1635198 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1635198 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1635198 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=25
#-----------
time=64646312
mem_heap_B=63988024
mem_heap_extra_B=658288
mem_stacks_B=0
heap_tree=detailed
n4: 63988024 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 28744704 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 28744704 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 28744704 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 28744704 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 28744704 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 28744704 0x400ABB: processfile (test_hm_file.c:78)
       n0: 28744704 0x40099B: main (test_hm_file.c:27)
 n1: 1688304 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1688304 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1688304 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=26
#-----------
time=66283768
mem_heap_B=65590446
mem_heap_extra_B=693322
mem_stacks_B=0
heap_tree=peak
n4: 65590446 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 33554432 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 33554432 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 33554432 0x400975: main (test_hm_file.c:24)
 n1: 30257152 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 30257152 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 30257152 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 30257152 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 30257152 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 30257152 0x400ABB: processfile (test_hm_file.c:78)
       n0: 30257152 0x40099B: main (test_hm_file.c:27)
 n1: 1778278 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 1778278 0x400AA6: processfile (test_hm_file.c:78)
   n0: 1778278 0x40099B: main (test_hm_file.c:27)
 n0: 584 in 2 places, all below massif's threshold (01.00%)
#-----------
snapshot=27
#-----------
time=67297712
mem_heap_B=64597978
mem_heap_extra_B=671846
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=28
#-----------
time=68370224
mem_heap_B=63548278
mem_heap_extra_B=649034
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=29
#-----------
time=69440432
mem_heap_B=62500928
mem_heap_extra_B=626176
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=30
#-----------
time=70536304
mem_heap_B=61428256
mem_heap_extra_B=602976
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=31
#-----------
time=71636576
mem_heap_B=60350956
mem_heap_extra_B=580004
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=32
#-----------
time=72735344
mem_heap_B=59275220
mem_heap_extra_B=556972
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=33
#-----------
time=73918784
mem_heap_B=58116364
mem_heap_extra_B=532388
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=34
#-----------
time=75159424
mem_heap_B=56901506
mem_heap_extra_B=506606
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=35
#-----------
time=76426256
mem_heap_B=55661368
mem_heap_extra_B=479912
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=36
#-----------
time=77720960
mem_heap_B=54394020
mem_heap_extra_B=452556
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=37
#-----------
time=79150544
mem_heap_B=52994610
mem_heap_extra_B=422382
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=38
#-----------
time=80608848
mem_heap_B=51566890
mem_heap_extra_B=391798
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=39
#-----------
time=82091552
mem_heap_B=50115450
mem_heap_extra_B=360534
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=40
#-----------
time=83575776
mem_heap_B=48662558
mem_heap_extra_B=329202
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=41
#-----------
time=85140832
mem_heap_B=47130668
mem_heap_extra_B=296036
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=42
#-----------
time=86731472
mem_heap_B=45573556
mem_heap_extra_B=262508
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=43
#-----------
time=88352880
mem_heap_B=43986176
mem_heap_extra_B=228480
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=44
#-----------
time=90000832
mem_heap_B=42372992
mem_heap_extra_B=193712
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=45
#-----------
time=91676752
mem_heap_B=40732576
mem_heap_extra_B=158208
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=46
#-----------
time=93519392
mem_heap_B=38928680
mem_heap_extra_B=119464
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=47
#-----------
time=95386160
mem_heap_B=37101156
mem_heap_extra_B=80220
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=48
#-----------
time=97280528
mem_heap_B=35246496
mem_heap_extra_B=40512
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=49
#-----------
time=99007920
mem_heap_B=33555540
mem_heap_extra_B=4076
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=50
#-----------
time=99008008
mem_heap_B=33555472
mem_heap_extra_B=4056
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=51
#-----------
time=99009040
mem_heap_B=33554448
mem_heap_extra_B=4048
mem_stacks_B=0
heap_tree=empty
#-----------
snapshot=52
#-----------
time=132567512
mem_heap_B=16
mem_heap_extra_B=8
mem_stacks_B=0
heap_tree=detailed
n5: 16 (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
 n1: 16 0x401301: hm_list_create (hm_list_hash.c:8)
  n0: 16 0x400975: main (test_hm_file.c:24)
 n1: 0 0x400F44: hm_hash_create (hm_hash.c:19)
  n1: 0 0x401324: hm_list_create (hm_list_hash.c:13)
   n0: 0 0x400975: main (test_hm_file.c:24)
 n1: 0 0x4E9821B: __fopen_internal (in /usr/lib/libc-2.20.so)
  n1: 0 0x400A66: processfile (test_hm_file.c:69)
   n0: 0 0x40099B: main (test_hm_file.c:27)
 n1: 0 0x400C45: hm_pair_create (hm_pair.c:46)
  n1: 0 0x400AA6: processfile (test_hm_file.c:78)
   n0: 0 0x40099B: main (test_hm_file.c:27)
 n1: 0 0x401857: _hm_vector_resize (hm_vector.c:164)
  n1: 0 0x401A8D: _hm_vector_shiftR (hm_vector.c:249)
   n1: 0 0x40159C: hm_vector_put (hm_vector.c:73)
    n1: 0 0x40107E: hm_hash_put (hm_hash.c:55)
     n1: 0 0x401389: hm_list_put (hm_list_hash.c:26)
      n1: 0 0x400ABB: processfile (test_hm_file.c:78)
       n0: 0 0x40099B: main (test_hm_file.c:27)
#-----------
snapshot=53
#-----------
time=132567536
mem_heap_B=0
mem_heap_extra_B=0
mem_stacks_B=0
heap_tree=empty
