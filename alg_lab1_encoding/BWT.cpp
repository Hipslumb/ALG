#include "functions.h"

//T(n) = O(n+k); S(n) = O(n+k)
void counting_sort(vector<vector<uc>>& data, int col) {
	int N = data.size();
	vector<int> count(256, 0);

	for (int i = 0; i < N; i++) 
		count[data[i][col]]++;

	for (int i = 1; i < 256; i++) {
		count[i] += count[i - 1];
	}

	vector<vector<uc>> out(N);
	for (int i = N - 1; i >= 0; i--) {
		uc c = data[i][col];
		int pos = --count[c];
		out[pos] = move(data[i]);
	}

	data = move(out);
}

//T(n) = O(n^2+nk); S(n) = O(n^2+k)
BWTnode bwt_encoding(vector <uc> data) {
	int N = data.size();
	vector<vector<uc>> BWmatrix(N, vector<uc>(N));

	for (int i = 0; i < N;i++) {
		for (int j = 0; j < N; j++) {
			BWmatrix[i][j] = data[(i + j) % N];
		}
	}
	for (int col = N - 1; col >= 0; col--)
		counting_sort(BWmatrix,col);
	int I = 0; bool found = true;

	for (int i = 0; i < N;i++) {
		bool found = true;
		for (int j = 0; j < N; j++) {
			if (BWmatrix[i][j] != data[j]) {
				found = false;
				break;
			}
		}
		if (found) {
			I = i;
			break;
		}
	}
	vector<uc> L(N);
	for (int i = 0; i < N;i++) {
		L[i] = BWmatrix[i][N - 1];
	}
	return { L,I };
}
//T(n) = O(n^3 + n^2k); S(n) = O(n^2+k)
vector <uc> bwt_decoding_matrix(BWTnode encoded) {
	int N = encoded.L.size();
	vector <uc> decoded(N);

	vector<vector<uc>> BWmatrix(N, vector<uc>(N));
	for (int j = 0; j < N; j++) {
		if (j > 0) {
			for (int r = 0;r < N;r++)
				for (int c = j - 1; c >= 0;c--)
					BWmatrix[r][c + 1] = BWmatrix[r][c];
		}
		for (int i = 0; i < N; i++) {
			BWmatrix[i][0] = encoded.L[i];
		}
		if (j < N) {
			for (int col = j; col >= 0; col--)
				counting_sort(BWmatrix, col);
		}
	}
	for (int j = 0; j < N; j++)
		decoded[j] = BWmatrix[encoded.I][j];
	return decoded;
}
//T(n) = O(n + k); S(n) = O(n + k)
vector <uc> bwt_decoding_LF(BWTnode encoded) {
	int N = encoded.L.size();
	vector <uc> decoded(N);
	vector <uc> last = encoded.L;

	vector<int> prev(N, 0);
	//counting sort for str
	vector<int> count(256, 0);

	//aabc - caab - 2 1 1
	for (int i = 0; i < N; i++)
		prev[i] = count[last[i]]++;

	//0 2 (0+2) 3 (2+1) 4 (3+1)
	int sum = 0;
	for (int i = 0; i < 256; i++) {
		int freq = count[i];
		count[i] = sum;
		sum += freq;
	}

	vector<int> LF(N);
	for (int i = 0; i < N; i++) {
		LF[i] = count[last[i]] + prev[i];
	}
	vector <uc> first(N);
	for (int i = N - 1; i >= 0; i--) {
		uc c = last[i];
		int pos = --count[c];
	}

	int i = encoded.I;
	decoded[N - 1] = last[i];
	for (int k = N - 2; k >= 0; k--) {
		decoded[k] = last[LF[i]];
		i = LF[i];
	}


	return decoded;
}

//but we can do: k = const = 256

vector<BWTnode> encoding_blocks(vector<uc>& data, int b_size) {
	vector<BWTnode> blocks;
	int N = data.size();

	for (int i = 0; i < N; i += b_size) {
		int cur_size = min(b_size, N - i);

		vector<uc> block_data(cur_size);
		for (int j = 0; j < cur_size; j++) {
			block_data[j] = data[i + j];
		}
		BWTnode encoded = bwt_encoding(block_data);
		blocks.push_back({ encoded.L, encoded.I });
	}

	return blocks;
}
vector<uc> decoding_blocks(vector<BWTnode>& blocks) {
	vector<uc> decoded;

	for (auto& block : blocks) {
		BWTnode encoded = { block.L, block.I };
		vector<uc> block_decoded = bwt_decoding_LF(encoded); //bwt_decoding_matrix(encoded);
		decoded.insert(decoded.end(), block_decoded.begin(), block_decoded.end());
	}

	return decoded;
}

vector<int> suff_vector(vector <uc> data) {
	int N = data.size();
	vector<int> suf_vect(N);
	for (int i = 0;i < N;i++) suf_vect[i] = i;

	sort(suf_vect.begin(), suf_vect.end(), [&](int a, int b) {
		while (a < N && b < N) {
			if (data[a] != data[b])
				return data[a] < data[b];
			a++;
			b++;
		}
		return a > b;
	});
	return suf_vect;
}

vector<uc> find_last(vector <uc> data) {
	int N = data.size();
	vector<int> suf_vect = suff_vector(data);
	vector<uc> last(N);
	for (int i = 0; i < N; i++) 
		last[i] = data[(suf_vect[i] + N - 1) % N];
	return last;
}