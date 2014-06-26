class Distribution {
	
	long[] counts;
	long max;

	Distribution(){
                counts = new long[256];
		max = 0;
		for(int i = 0; i < 256; ++i)
			counts[i] = 0;
	}

	void register(int b){
		counts[b]++;
		if(counts[b] > max)
			max = counts[b];
	}

	void draw(int x, int y, int w, int h){
		fill(0);
                stroke(250,0,0);
		rect(x, y, w, h);
		fill(250);
		for(int i = 0; i < w; ++i){
			int xval = int(map(i, 0, w, 0, 256));
			float yval = map(counts[xval], 0, max, 0, h);
                        line(x + i, y + h, x + i, y + h - yval / 2);
		}
	}
}
