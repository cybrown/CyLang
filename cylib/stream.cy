class Stream {
	virtual byte[] read(int len) {
		return {byte*1};
	}

	virtual int write(byte[] data, int len) {
		return 0;
	}
}
