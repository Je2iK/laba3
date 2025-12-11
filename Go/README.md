# Go Data Structures Project

## Project Structure
```
├── src/                   # Source files (.go)
├── tests/                 # Test files (*_test.go)
├── coverage/              # Coverage reports
└── README.md             # This file
```

## Data Structures Implemented
- Stack
- Queue  
- Array
- ForwardList
- RedBlackTree (replaced AVL)
- ChainHashTable (replaced Cuckoo)

## Build & Test
```bash
cd src/
go test ../tests/ -coverprofile=../coverage/coverage.out
go tool cover -html=../coverage/coverage.out -o ../coverage/coverage.html
```

## Run Demo
```bash
cd src/
go run .
```

## Coverage: 85.0%
View HTML report: `coverage/coverage.html`
