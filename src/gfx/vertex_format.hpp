#ifndef VERTEX_FORMAT_HPP
#define VERTEX_FORMAT_HPP

namespace mg {
	//P = position
	//N = normal 
	//T = texture coordinate
	//C = color
	enum class VertexFormat {
		P,
		N,
		T,
		C,
	
		PP,
		NN,
		TT,
		CC,
	
		PPP,
		NNN,
		TTT,
		CCC,
	
		PPPP,
		NNNN,
		TTTT,
		CCCC,
	
		PN,
		PT,
		PTC,
		PNTC,
	
		PPPTT,
		PPTTCCC,
		PPPTTCCC,
		PPPTTCCCC,
	
		PPPNNN,
	};
}

#endif //VERTEX_FORMAT_HPP
