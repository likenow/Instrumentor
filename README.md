# Instrumentor


## QuickStart

### import header file

```c++
#include "Instrumentor.h"

```

### scope your code

```c++

  Instrumentor::Get().BeginSession("Profile", filepath);
	// your code
	Instrumentor::Get().EndSession();

```

### Drag json file to `Chrome://tracing`
