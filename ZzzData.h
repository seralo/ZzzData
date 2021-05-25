/***************************************************************
  ZzzData.h
***************************************************************/
#ifndef ZZZ_DATA_H
#define ZZZ_DATA_H


/**
 * Abstract class to define default data manipulation functions.
 *
 * T     is the type of data (default=int). Could be uint8_t, int8_t, uint16_t, int, float...
 */
template <typename T=int> class ZzzData {
	public:
		/** Reset state */
		void reset();
		/** Add data to process */
		T add(T input);
		/** Get last value */
		T get() {

};

/**
 * Base class to only store data
 *
 * T     is the type of data (default=int). Could be uint8_t, int8_t, uint16_t, int, float...
 */
template <typename T=int, T DEFAULT_RESULT=-1> class ZzzDataValue : public ZzzData<T> {
	protected:
		T _last;

	public:
		void reset() {
			_last=DEFAULT_RESULT;
		}
		
		ZzzDataValue() {
			reset();
		}
		
		T add(T input) {
			_last=input;
			return _last;
		}

		T get() {
			return _last; 
		}	
};

/**
 * Keep minimum and maximum values of a given set of data
 *
 * T     is the type of data (default=int). Could be uint8_t, int8_t, uint16_t, int, float...
 */
template <typename T=int, T DEFAULT_RESULT=-1> class ZzzDataMinMax : public ZzzDataValue<T, DEFAULT_RESULT> {
	protected:
		T _min;
		T _max;
		bool _first;

	public:
		/** Next value will define min and max */
		void reset() {
			_first=true;
			_last=DEFAULT_RESULT;
		}
		
		/** Constructor first value define min and max */
		ZzzDataMinMax() {
			reset();
		}
		
		/** Constructor with initial minimum and maximum values */
		ZzzDataMinMax(T min, T max) {
			_min=min;
			_max=max;
			_first=false;
		}

		/** Fill all values with given value */
		void fill(T value) {
			_min=value;
			_max=value;
			_first=false;
		}
		
		/**
		 * Add a new value and compute min and max.
		 * @return the input
		 */
		T add(T input) {
			_last=input;
			if (_first) {
				fill(input);
			}
			else {
				if (input>_max)
					_max=input;
				if (input<_min)
					_min=input;
			}
			return input;
		}
		
		/** Get current minimum value */
		T min() final {
			return _min; 
		}	

		/** Get current maximum value */
		T max() final {
			return _max; 
		}	
};


/**
 * Keep the history of a set of values.
 *
 * N     is the number of values to keep.
 * T     is the type of data (default=int). Could be uint8_t, int8_t, uint16_t, int, float...
 */
template <size_t N, typename T=int> class ZzzDataHistory : public ZzzData<T> {
	protected:
		T _data[N];
		size_t _current;
		bool _first;

	public:
		/** Next value will be filled */
		void reset() {
			_first=true;
			_current=N-1;
		}

		/** Fill all values with given value */
		void fill(T value) {
			for (size_t i=0; i<N; i++) {
				_data[i]=value;
			}
			_current=N-1;
			_first=false;
		}

		/** Constructor first value will be filled */
		ZzzDataHistory() {
			reset();
		}

		/**
		 * Add a new value and compute the new moving average.
		 * @return the new moving average
		 */
		T add(T input) {
			if (_first) {
				fill(input);
			}
			else {
				//Compute new index
				_current++;
				if (_current>=N) {
					_current=0;
	    			}
				_data[_current]=input;
	    		}
			return input;
		}

		/** Get last value added */
		T get() {
			return getLast(); 
		}

		/**
		 * Get previous value
		 * getLast(), or getLast(0) return the last added value
		 * getLast(1) return value added before the last one
		 * ...
		 * getLast(N-1) return the last value accessible
		 */
		T getLast(size_t back=0) {
			//ie: (N=4) _current=1 back 0,1,2,3 => returns 1,0,3,2
			if (back>=N) {
				back=N-1;
			}
			if (_current>=back) {
				return _data[_current-back];
			}
			else {
				return _data[N+_current-back];
			}
		}

		/** Get data size */
		size_t size() {
			return N;
		}
};


#endif

