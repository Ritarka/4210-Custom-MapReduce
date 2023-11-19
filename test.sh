test:
	bin/mr_worker localhost:50051 & bin/mr_worker localhost:50052
	bin/mrdemo
.PHONY: test

demo:
	cd bin && ./mrdemo && cd ..
.PHONY: demo