# confTainter

## Dependency
```
llvm-10.0.0
```

## Build
```
cd tainter
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++-10 -DCMAKE_C_COMPILER=/usr/bin/clang-10 -DLLVM_DIR=/usr/lib/llvm-10/cmake . 
make
```

## Usage
```
cd test/demo
../../tainter test.bc test-var.txt
```
## Check results
```
cat test-records.dat
```

## Example result
```
Tainted Functions (group by Caller-Functions): 

		Clone_Handle::open_file <------------ func-1 of "srv_unix_file_flush_method"
				Clone_Task_Manager::set_error ----- Tainted Function.

		Clone_Snapshot::update_block_size <-- func-2 of "srv_unix_file_flush_method"
				os_event_set -------------------\ 
				pfs_unlock_mutex_v1              |_ Tainted Function.
				sync_array_object_signalled      |
				ut_dbg_assertion_failed --------/

		Double_write::sync_page_flush <------ func-3 of "srv_unix_file_flush_method"
				__clang_call_terminate ---------\ 
				buf_page_io_complete             |-- Tainted Function.
				fil_flush ----------------------/
        
    ...
```
