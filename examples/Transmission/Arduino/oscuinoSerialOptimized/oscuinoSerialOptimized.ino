#include <OSCBundle.h>
#include <OSCMessage.h>

/*
  This example is meant to be used with the MAX/MSP 
  to Arduino Interface called oscuinoSerial.maxpatch
  
  */


#include <SLIPEncodedSerial.h>

OSCBundle bundle(SLIPSerial);
OSCBundle bundleOUT(SLIPSerial);


//many definitions and abstractions are taken from OSCuino 1.0 by Adrian Freed 2011
static PROGMEM float floattable[1024] = {
	0.000000, 0.000978, 0.001955, 0.002933, 0.003910, 0.004888, 0.005865, 0.006843, 0.007820, 0.008798, 0.009775, 
	0.010753, 0.011730, 0.012708, 0.013685, 0.014663, 0.015640, 0.016618, 0.017595, 0.018573, 0.019550, 
	0.020528, 0.021505, 0.022483, 0.023460, 0.024438, 0.025415, 0.026393, 0.027370, 0.028348, 0.029326, 
	0.030303, 0.031281, 0.032258, 0.033236, 0.034213, 0.035191, 0.036168, 0.037146, 0.038123, 0.039101, 
	0.040078, 0.041056, 0.042033, 0.043011, 0.043988, 0.044966, 0.045943, 0.046921, 0.047898, 0.048876, 
	0.049853, 0.050831, 0.051808, 0.052786, 0.053763, 0.054741, 0.055718, 0.056696, 0.057674, 0.058651, 
	0.059629, 0.060606, 0.061584, 0.062561, 0.063539, 0.064516, 0.065494, 0.066471, 0.067449, 0.068426, 
	0.069404, 0.070381, 0.071359, 0.072336, 0.073314, 0.074291, 0.075269, 0.076246, 0.077224, 0.078201, 
	0.079179, 0.080156, 0.081134, 0.082111, 0.083089, 0.084066, 0.085044, 0.086022, 0.086999, 0.087977, 
	0.088954, 0.089932, 0.090909, 0.091887, 0.092864, 0.093842, 0.094819, 0.095797, 0.096774, 0.097752, 
	0.098729, 0.099707, 0.100684, 0.101662, 0.102639, 0.103617, 0.104594, 0.105572, 0.106549, 0.107527, 
	0.108504, 0.109482, 0.110459, 0.111437, 0.112414, 0.113392, 0.114370, 0.115347, 0.116325, 0.117302, 
	0.118280, 0.119257, 0.120235, 0.121212, 0.122190, 0.123167, 0.124145, 0.125122, 0.126100, 0.127077, 
	0.128055, 0.129032, 0.130010, 0.130987, 0.131965, 0.132942, 0.133920, 0.134897, 0.135875, 0.136852, 
	0.137830, 0.138807, 0.139785, 0.140762, 0.141740, 0.142717, 0.143695, 0.144673, 0.145650, 0.146628, 
	0.147605, 0.148583, 0.149560, 0.150538, 0.151515, 0.152493, 0.153470, 0.154448, 0.155425, 0.156403, 
	0.157380, 0.158358, 0.159335, 0.160313, 0.161290, 0.162268, 0.163245, 0.164223, 0.165200, 0.166178, 
	0.167155, 0.168133, 0.169110, 0.170088, 0.171065, 0.172043, 0.173021, 0.173998, 0.174976, 0.175953, 
	0.176931, 0.177908, 0.178886, 0.179863, 0.180841, 0.181818, 0.182796, 0.183773, 0.184751, 0.185728, 
	0.186706, 0.187683, 0.188661, 0.189638, 0.190616, 0.191593, 0.192571, 0.193548, 0.194526, 0.195503, 
	0.196481, 0.197458, 0.198436, 0.199413, 0.200391, 0.201369, 0.202346, 0.203324, 0.204301, 0.205279, 
	0.206256, 0.207234, 0.208211, 0.209189, 0.210166, 0.211144, 0.212121, 0.213099, 0.214076, 0.215054, 
	0.216031, 0.217009, 0.217986, 0.218964, 0.219941, 0.220919, 0.221896, 0.222874, 0.223851, 0.224829, 
	0.225806, 0.226784, 0.227761, 0.228739, 0.229717, 0.230694, 0.231672, 0.232649, 0.233627, 0.234604, 
	0.235582, 0.236559, 0.237537, 0.238514, 0.239492, 0.240469, 0.241447, 0.242424, 0.243402, 0.244379, 
	0.245357, 0.246334, 0.247312, 0.248289, 0.249267, 0.250244, 0.251222, 0.252199, 0.253177, 0.254154, 
	0.255132, 0.256109, 0.257087, 0.258065, 0.259042, 0.260020, 0.260997, 0.261975, 0.262952, 0.263930, 
	0.264907, 0.265885, 0.266862, 0.267840, 0.268817, 0.269795, 0.270772, 0.271750, 0.272727, 0.273705, 
	0.274682, 0.275660, 0.276637, 0.277615, 0.278592, 0.279570, 0.280547, 0.281525, 0.282502, 0.283480, 
	0.284457, 0.285435, 0.286413, 0.287390, 0.288368, 0.289345, 0.290323, 0.291300, 0.292278, 0.293255, 
	0.294233, 0.295210, 0.296188, 0.297165, 0.298143, 0.299120, 0.300098, 0.301075, 0.302053, 0.303030, 
	0.304008, 0.304985, 0.305963, 0.306940, 0.307918, 0.308895, 0.309873, 0.310850, 0.311828, 0.312805, 
	0.313783, 0.314761, 0.315738, 0.316716, 0.317693, 0.318671, 0.319648, 0.320626, 0.321603, 0.322581, 
	0.323558, 0.324536, 0.325513, 0.326491, 0.327468, 0.328446, 0.329423, 0.330401, 0.331378, 0.332356, 
	0.333333, 0.334311, 0.335288, 0.336266, 0.337243, 0.338221, 0.339198, 0.340176, 0.341153, 0.342131, 
	0.343109, 0.344086, 0.345064, 0.346041, 0.347019, 0.347996, 0.348974, 0.349951, 0.350929, 0.351906, 
	0.352884, 0.353861, 0.354839, 0.355816, 0.356794, 0.357771, 0.358749, 0.359726, 0.360704, 0.361681, 
	0.362659, 0.363636, 0.364614, 0.365591, 0.366569, 0.367546, 0.368524, 0.369501, 0.370479, 0.371457, 
	0.372434, 0.373412, 0.374389, 0.375367, 0.376344, 0.377322, 0.378299, 0.379277, 0.380254, 0.381232, 
	0.382209, 0.383187, 0.384164, 0.385142, 0.386119, 0.387097, 0.388074, 0.389052, 0.390029, 0.391007, 
	0.391984, 0.392962, 0.393939, 0.394917, 0.395894, 0.396872, 0.397849, 0.398827, 0.399804, 0.400782, 
	0.401760, 0.402737, 0.403715, 0.404692, 0.405670, 0.406647, 0.407625, 0.408602, 0.409580, 0.410557, 
	0.411535, 0.412512, 0.413490, 0.414467, 0.415445, 0.416422, 0.417400, 0.418377, 0.419355, 0.420332, 
	0.421310, 0.422287, 0.423265, 0.424242, 0.425220, 0.426197, 0.427175, 0.428152, 0.429130, 0.430108, 
	0.431085, 0.432063, 0.433040, 0.434018, 0.434995, 0.435973, 0.436950, 0.437928, 0.438905, 0.439883, 
	0.440860, 0.441838, 0.442815, 0.443793, 0.444770, 0.445748, 0.446725, 0.447703, 0.448680, 0.449658, 
	0.450635, 0.451613, 0.452590, 0.453568, 0.454545, 0.455523, 0.456500, 0.457478, 0.458456, 0.459433, 
	0.460411, 0.461388, 0.462366, 0.463343, 0.464321, 0.465298, 0.466276, 0.467253, 0.468231, 0.469208, 
	0.470186, 0.471163, 0.472141, 0.473118, 0.474096, 0.475073, 0.476051, 0.477028, 0.478006, 0.478983, 
	0.479961, 0.480938, 0.481916, 0.482893, 0.483871, 0.484848, 0.485826, 0.486804, 0.487781, 0.488759, 
	0.489736, 0.490714, 0.491691, 0.492669, 0.493646, 0.494624, 0.495601, 0.496579, 0.497556, 0.498534, 
	0.499511, 0.500489, 0.501466, 0.502444, 0.503421, 0.504399, 0.505376, 0.506354, 0.507331, 0.508309, 
	0.509286, 0.510264, 0.511241, 0.512219, 0.513196, 0.514174, 0.515152, 0.516129, 0.517107, 0.518084, 
	0.519062, 0.520039, 0.521017, 0.521994, 0.522972, 0.523949, 0.524927, 0.525904, 0.526882, 0.527859, 
	0.528837, 0.529814, 0.530792, 0.531769, 0.532747, 0.533724, 0.534702, 0.535679, 0.536657, 0.537634, 
	0.538612, 0.539589, 0.540567, 0.541544, 0.542522, 0.543500, 0.544477, 0.545455, 0.546432, 0.547410, 
	0.548387, 0.549365, 0.550342, 0.551320, 0.552297, 0.553275, 0.554252, 0.555230, 0.556207, 0.557185, 
	0.558162, 0.559140, 0.560117, 0.561095, 0.562072, 0.563050, 0.564027, 0.565005, 0.565982, 0.566960, 
	0.567937, 0.568915, 0.569892, 0.570870, 0.571848, 0.572825, 0.573803, 0.574780, 0.575758, 0.576735, 
	0.577713, 0.578690, 0.579668, 0.580645, 0.581623, 0.582600, 0.583578, 0.584555, 0.585533, 0.586510, 
	0.587488, 0.588465, 0.589443, 0.590420, 0.591398, 0.592375, 0.593353, 0.594330, 0.595308, 0.596285, 
	0.597263, 0.598240, 0.599218, 0.600196, 0.601173, 0.602151, 0.603128, 0.604106, 0.605083, 0.606061, 
	0.607038, 0.608016, 0.608993, 0.609971, 0.610948, 0.611926, 0.612903, 0.613881, 0.614858, 0.615836, 
	0.616813, 0.617791, 0.618768, 0.619746, 0.620723, 0.621701, 0.622678, 0.623656, 0.624633, 0.625611, 
	0.626588, 0.627566, 0.628543, 0.629521, 0.630499, 0.631476, 0.632454, 0.633431, 0.634409, 0.635386, 
	0.636364, 0.637341, 0.638319, 0.639296, 0.640274, 0.641251, 0.642229, 0.643206, 0.644184, 0.645161, 
	0.646139, 0.647116, 0.648094, 0.649071, 0.650049, 0.651026, 0.652004, 0.652981, 0.653959, 0.654936, 
	0.655914, 0.656891, 0.657869, 0.658847, 0.659824, 0.660802, 0.661779, 0.662757, 0.663734, 0.664712, 
	0.665689, 0.666667, 0.667644, 0.668622, 0.669599, 0.670577, 0.671554, 0.672532, 0.673509, 0.674487, 
	0.675464, 0.676442, 0.677419, 0.678397, 0.679374, 0.680352, 0.681329, 0.682307, 0.683284, 0.684262, 
	0.685239, 0.686217, 0.687195, 0.688172, 0.689150, 0.690127, 0.691105, 0.692082, 0.693060, 0.694037, 
	0.695015, 0.695992, 0.696970, 0.697947, 0.698925, 0.699902, 0.700880, 0.701857, 0.702835, 0.703812, 
	0.704790, 0.705767, 0.706745, 0.707722, 0.708700, 0.709677, 0.710655, 0.711632, 0.712610, 0.713587, 
	0.714565, 0.715543, 0.716520, 0.717498, 0.718475, 0.719453, 0.720430, 0.721408, 0.722385, 0.723363, 
	0.724340, 0.725318, 0.726295, 0.727273, 0.728250, 0.729228, 0.730205, 0.731183, 0.732160, 0.733138, 
	0.734115, 0.735093, 0.736070, 0.737048, 0.738025, 0.739003, 0.739980, 0.740958, 0.741935, 0.742913, 
	0.743891, 0.744868, 0.745846, 0.746823, 0.747801, 0.748778, 0.749756, 0.750733, 0.751711, 0.752688, 
	0.753666, 0.754643, 0.755621, 0.756598, 0.757576, 0.758553, 0.759531, 0.760508, 0.761486, 0.762463, 
	0.763441, 0.764418, 0.765396, 0.766373, 0.767351, 0.768328, 0.769306, 0.770283, 0.771261, 0.772239, 
	0.773216, 0.774194, 0.775171, 0.776149, 0.777126, 0.778104, 0.779081, 0.780059, 0.781036, 0.782014, 
	0.782991, 0.783969, 0.784946, 0.785924, 0.786901, 0.787879, 0.788856, 0.789834, 0.790811, 0.791789, 
	0.792766, 0.793744, 0.794721, 0.795699, 0.796676, 0.797654, 0.798631, 0.799609, 0.800587, 0.801564, 
	0.802542, 0.803519, 0.804497, 0.805474, 0.806452, 0.807429, 0.808407, 0.809384, 0.810362, 0.811339, 
	0.812317, 0.813294, 0.814272, 0.815249, 0.816227, 0.817204, 0.818182, 0.819159, 0.820137, 0.821114, 
	0.822092, 0.823069, 0.824047, 0.825024, 0.826002, 0.826979, 0.827957, 0.828935, 0.829912, 0.830890, 
	0.831867, 0.832845, 0.833822, 0.834800, 0.835777, 0.836755, 0.837732, 0.838710, 0.839687, 0.840665, 
	0.841642, 0.842620, 0.843597, 0.844575, 0.845552, 0.846530, 0.847507, 0.848485, 0.849462, 0.850440, 
	0.851417, 0.852395, 0.853372, 0.854350, 0.855327, 0.856305, 0.857283, 0.858260, 0.859238, 0.860215, 
	0.861193, 0.862170, 0.863148, 0.864125, 0.865103, 0.866080, 0.867058, 0.868035, 0.869013, 0.869990, 
	0.870968, 0.871945, 0.872923, 0.873900, 0.874878, 0.875855, 0.876833, 0.877810, 0.878788, 0.879765, 
	0.880743, 0.881720, 0.882698, 0.883675, 0.884653, 0.885630, 0.886608, 0.887586, 0.888563, 0.889541, 
	0.890518, 0.891496, 0.892473, 0.893451, 0.894428, 0.895406, 0.896383, 0.897361, 0.898338, 0.899316, 
	0.900293, 0.901271, 0.902248, 0.903226, 0.904203, 0.905181, 0.906158, 0.907136, 0.908113, 0.909091, 
	0.910068, 0.911046, 0.912023, 0.913001, 0.913978, 0.914956, 0.915934, 0.916911, 0.917889, 0.918866, 
	0.919844, 0.920821, 0.921799, 0.922776, 0.923754, 0.924731, 0.925709, 0.926686, 0.927664, 0.928641, 
	0.929619, 0.930596, 0.931574, 0.932551, 0.933529, 0.934506, 0.935484, 0.936461, 0.937439, 0.938416, 
	0.939394, 0.940371, 0.941349, 0.942326, 0.943304, 0.944282, 0.945259, 0.946237, 0.947214, 0.948192, 
	0.949169, 0.950147, 0.951124, 0.952102, 0.953079, 0.954057, 0.955034, 0.956012, 0.956989, 0.957967, 
	0.958944, 0.959922, 0.960899, 0.961877, 0.962854, 0.963832, 0.964809, 0.965787, 0.966764, 0.967742, 
	0.968719, 0.969697, 0.970674, 0.971652, 0.972630, 0.973607, 0.974585, 0.975562, 0.976540, 0.977517, 
	0.978495, 0.979472, 0.980450, 0.981427, 0.982405, 0.983382, 0.984360, 0.985337, 0.986315, 0.987292, 
	0.988270, 0.989247, 0.990225, 0.991202, 0.992180, 0.993157, 0.994135, 0.995112, 0.996090, 0.997067, 
	0.998045, 0.999022, 1.000000, 
};


static inline float floatfrom10bitint(int n)
{
	return pgm_read_float(floattable+constrain(n,0,1023));
}

inline void digitalPullup(uint8_t pin, boolean b) { 
	pinMode(pin, INPUT); 
	digitalWrite(pin, b?HIGH:LOW); 
}

#if defined(__AVR_ATmega1280__)
#define ANALOG_PINS 16
const int DIGITAL_PINS=54;
inline void analogPullup(uint8_t pin, boolean b) { 
	digitalPullup(pin+54,b); 
}
inline void analogOutWrite(uint8_t pin, uint8_t b) {
	pinMode(pin+54, OUTPUT);  
	digitalWrite(pin+54,b);
}

inline void analogPWMWrite(uint8_t pin, uint8_t b) {
	pinMode(pin+54, OUTPUT);  
	analogWrite(pin+54,b);
}

#else
// teensy++
#if defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)

#define ANALOG_PINS 8
const int DIGITAL_PINS=38;
inline void analogPullup(uint8_t pin, boolean b) { 
	pinMode(38+pin,b?INPUT_PULLUP: INPUT); 
}
inline void analogOutWrite(uint8_t pin, uint8_t b) {
	pinMode(38+pin, OUTPUT);  // change directions of an analog pin
	digitalWrite(38+pin,b); 
}

inline void analogPWMWrite(uint8_t pin, uint8_t b) {
	pinMode(38+pin, OUTPUT);  // change directions of an analog pin
	analogWrite(38+pin,b); 
}
#else
//AT90USB1286 teensy++
#if defined(__AVR_ATmega32U4__)
//teensy 2.0
#define ANALOG_PINS 12
const int DIGITAL_PINS=11; // actually the teensy 2.0 has two more non contiguously addressed (22 and 23)
inline void analogPullup(uint8_t pin, boolean b) { 
	if(pin==11)
		pin = -1; // ouch read the diagram carefully! http://www.pjrc.com/teensy/pinout.html
	pinMode(21-pin,b?INPUT_PULLUP: INPUT); 
}
typedef enum {
	endOfpinlist=-1, a0=14,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15 } 
pinnames;
inline void analogOutWrite(uint8_t pin, uint8_t b) {
	if(pin==11)
		pin = -1; // ouch
	pinMode(21-pin, OUTPUT);  // change directions of an analog pin
	digitalWrite(21-pin,b); 
}
inline void analogPWMWrite(uint8_t pin, uint8_t b) {
	if(pin==11)
		pin = -1; // ouch
	pinMode(21-pin, OUTPUT);  // change directions of an analog pin
	analogWrite(21-pin,b); 
}
#else
//6 or 8 depending
#define ANALOG_PINS 8
const int DIGITAL_PINS=13;
inline void analogPullup(uint8_t pin, boolean b) { 
	digitalPullup(pin+14,b?HIGH:LOW); 
}

inline void analogOutWrite(uint8_t pin, uint8_t b) {
	
	pinMode(pin+14, OUTPUT);  // change directions of an analog pin
	digitalWrite(pin+14,b); 
}
inline void analogPWMWrite(uint8_t pin, uint8_t b) {
	
	pinMode(pin+14, OUTPUT);  // change directions of an analog pin
	analogWrite(pin+14,b); 
}
#endif
#endif
#endif

float getSupplyVoltage(){
#if !defined(__AVR_ATmega8__)
    // temperature and power supply measurement on some Arduinos 
    // powersupply
    int result;
    // Read 1.1V reference against AVcc
#if defined(__AVR_ATmega32U4__)
    ADMUX = 0x40 | _BV(MUX4)| _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    ADCSRB =  0;
    //  ADCSRB = DEFAULT_ADCSRB | (1<<MUX5);
#elif  defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)    || defined(__AVR_ATmega1280__) 
    ADMUX = 0x40| _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1) ;
    ADCSRB =  0;
#else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif
    delayMicroseconds(300); // wait for Vref to settle
    ADCSRA |= _BV(ADSC); // Convert
    while (bit_is_set(ADCSRA,ADSC));
	result = ADCL;
    result |= ADCH<<8;
    
    
    float supplyvoltage = 1.1264 *1023 / result;
    return supplyvoltage;
#endif  
	
	
}

float getTemperature(){
	
	int result;
#if defined(__AVR_ATmega32U4__) ||    (!defined(__AVR_ATmega1280__) && !defined(__AVR_ATmega8__) && !defined(__AVR_AT90USB646__) && !defined(__AVR_AT90USB1286__))
	// temperature
	
#if defined(__AVR_ATmega32U4__)
	ADMUX =  _BV(REFS1) | _BV(REFS0) | _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
	ADCSRB =  _BV(MUX5);
#else
	ADMUX = _BV(REFS1) | _BV(REFS0) | _BV(MUX3);
#endif
	
	
	delayMicroseconds(200); // wait for Vref to settle
	ADCSRA |= _BV(ADSC); // Convert
	while (bit_is_set(ADCSRA,ADSC));
	result = ADCL;
	result |= ADCH<<8;
	
	float temp = result/1023.0;
	return temp;
	analogReference(DEFAULT);
#endif	
}

char pinString[54][4] = {"/0" ,"/1" ,"/2" ,"/3" ,"/4" ,"/5" ,"/6" ,"/7" ,"/8" ,"/9" ,"/10" ,"/11" ,"/12" ,"/13" ,"/14" ,"/15" ,"/16" ,"/17" ,"/18" ,"/19" ,"/20" ,"/21" ,"/22" ,"/23" ,"/24" ,"/25" ,"/26" ,"/27" ,"/28" ,"/29" ,"/30" ,"/31" ,"/32" ,"/33" ,"/34" ,"/35" ,"/36" ,"/37" ,"/38" ,"/39" ,"/40" ,"/41" ,"/42" ,"/43" ,"/44" ,"/45" ,"/46" ,"/47" ,"/48" ,"/49" ,"/50" ,"/51" ,"/52" ,"/53"};

/*
  The main part of the program. 
*/

void setup() {
  //setup ethernet part
  SLIPSerial.begin(115200);
}

boolean analogReadMode = false;
boolean digitalReadMode = false;
boolean analogPullupReadMode = false;
boolean digitalPullupReadMode = false;

void loop(){
  bundle.clear();  
  //read the incoming message
  bundleReceive();
  pollingMode();
}



void bundleReceive(){ 
  if (bundle.receive()>0){
     // "/*"  = "/\052" 
     //bc of a bug in the Arduino IDE, it won't compile with "/*" in a string.
     //long tm1 = micros();
     //long tm2 = micros();
     //bundleOUT.addMessage("/t/a").add(tm2-tm1);
     bundle.route("/a", handleAnalog);
     sendBundle();
     bundle.route("/d", handleDigital);
     sendBundle();
     bundle.route("/s", handleSystem);
     sendBundle();
     bundle.route("/m", handleMode);
  }
}

void sendBundle(){
  //send the outgoing message
  if(bundleOUT.size()){
    bundleOUT.send();
    SLIPSerial.endTransmission(); 
    #if defined(CORE_TEENSY)
    Serial.send_now();
    #endif
  } 
}

/*
ANALOG METHODS
*/

inline void addAnalogRead(char * address, int pin){
  analogPullup(pin, false);
  bundleOUT.addMessage(address).add(analogRead(pin));
}

void routeAnalogRead(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < ANALOG_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      //message is asking for an analog read
      if (msg.isString()){
        char addrBuff[16];
        msg.getString(addrBuff);
        addAnalogRead(addrBuff, i);
      } else {
        char outputAddr[8] = "/a/i/xx";
        //put the pin num in the output address
        outputAddr[5] = pinString[i][1];
        outputAddr[6] = pinString[i][2];
        addAnalogRead(outputAddr, i);
      }
    } 
  }
}

inline void addAnalogPullupRead(char * address, int pin){
  analogPullup(pin, true);
  bundleOUT.addMessage(address).add(analogRead(pin));
}

void routeAnalogPullupRead(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < ANALOG_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      //message is asking for an analog read
      if (msg.isString()){
        char addrBuff[16];
        msg.getString(addrBuff);
        addAnalogPullupRead(addrBuff, i);
      } else {
        char outputAddr[8] = "/a/u/xx";
        //put the pin num in the output address
        outputAddr[5] = pinString[i][1];
        outputAddr[6] = pinString[i][2];
        addAnalogPullupRead(outputAddr, i);
      }
    } 
  }
}

void routeAnalogOut(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < ANALOG_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      analogOutWrite(i, msg.getInt());
    } 
  }  
}

void routeAnalogPWM(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < ANALOG_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      analogPWMWrite(i, msg.getInt());
    } 
  }  
}

void handleAnalog(OSCMessage msg, int addrOffset ){
  msg.route("/i", routeAnalogRead, addrOffset);
  msg.route("/u", routeAnalogPullupRead, addrOffset);
  msg.route("/o", routeAnalogOut, addrOffset);
  msg.route("/p", routeAnalogPWM, addrOffset);  
}

/*
DIGITAL METHODS
*/
inline void addDigitalRead(char * address, int pin){
  digitalPullup(pin, false);
  bundleOUT.addMessage(address).add(digitalRead(pin));
}

void routeDigitalRead(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < DIGITAL_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      //message is asking for an analog read
      if (msg.isString()){
        char addrBuff[16];
        msg.getString(addrBuff);
        addDigitalRead(addrBuff, i);
      } else {
        char outputAddr[8] = "/d/i/xx";
        //put the pin num in the output address
        outputAddr[5] = pinString[i][1];
        outputAddr[6] = pinString[i][2];
        addDigitalRead(outputAddr, i);
      }
    } 
  }
}

inline void addDigitalPullupRead(char * address, int pin){
  digitalPullup(pin, true);
  bundleOUT.addMessage(address).add(digitalRead(pin));
}

void routeDigitalPullupRead(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < DIGITAL_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      //message is asking for an analog read
      if (msg.isString()){
        char addrBuff[16];
        msg.getString(addrBuff);
        addDigitalPullupRead(addrBuff, i);
      } else {
        char outputAddr[8] = "/d/u/xx";
        //put the pin num in the output address
        outputAddr[5] = pinString[i][1];
        outputAddr[6] = pinString[i][2];
        addDigitalPullupRead(outputAddr, i);
      }
    } 
  }
}

void routeDigitalOut(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < DIGITAL_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      pinMode(i, OUTPUT);
      digitalWrite(i, msg.getInt());
    } 
  }  
}

void routeDigitalPWM(OSCMessage msg, int addrOffset){
  for(byte i = 0; i < DIGITAL_PINS; i++){
    if(msg.match(pinString[i], addrOffset)){
      analogWrite(i, msg.getInt());
    } 
  }  
}

void handleDigital(OSCMessage msg, int addrOffset ){
  msg.route("/i", routeDigitalRead, addrOffset);
  msg.route("/u", routeDigitalPullupRead, addrOffset);
  msg.route("/o", routeDigitalOut, addrOffset);  
  msg.route("/p", routeDigitalPWM, addrOffset);  
}

/*
 SYSTEM MESSAGES
*/

void handleSystem(OSCMessage msg, int addrOffset ){
  /*
  //handle the temp.
  if (msg.fullMatch("/t", addrOffset)){
    bundleOUT.addMessage("/s/t").add(getTemperature());
  }*/
  if (msg.fullMatch("/p", addrOffset)){
    bundleOUT.addMessage("/s/p").add(getSupplyVoltage());
  }
  if (msg.fullMatch("/m", addrOffset)){
    bundleOUT.addMessage("/s/m").add(long(micros()));
     
  }
  if (msg.fullMatch("/d", addrOffset)){
    bundleOUT.addMessage("/s/d").add(DIGITAL_PINS);
     
  }
  if (msg.fullMatch("/a", addrOffset)){
    bundleOUT.addMessage("/s/a").add(ANALOG_PINS);
  }
}

/*
 MODE MESSAGES
*/

void handleMode(OSCMessage msg, int addrOffset ){
  msg.route("/u", handlePullupMode, addrOffset);
  msg.route("/i", handleInputMode, addrOffset);
}

void handlePullupMode(OSCMessage msg, int addrOffset ){
  if (msg.fullMatch("/a", addrOffset)){
    if (msg.getInt()){
      analogPullupReadMode = true;
    } else {
      analogPullupReadMode = false;
    }
  }
  if (msg.fullMatch("/d", addrOffset)){
    if (msg.getInt()){
      digitalPullupReadMode = true;
    } else {
      digitalPullupReadMode = false;
    }
  }
}

void handleInputMode(OSCMessage msg, int addrOffset ){
  if (msg.fullMatch("/a", addrOffset)){
    if (msg.getInt()){
      analogReadMode = true;
    } else {
      analogReadMode = false;
    }
  }
  if (msg.fullMatch("/d", addrOffset)){
    if (msg.getInt()){
      digitalReadMode = true;
    } else {
      digitalReadMode = false;
    }
  }
}

void doDigitalRead(){
  int bundleSize = 0;
  for(byte i = 0; i < DIGITAL_PINS; i++){
    bundleSize++;
    char outputAddr[8] = "/d/i/xx";
    outputAddr[5] = pinString[i][1];
    outputAddr[6] = pinString[i][2];
    addDigitalRead(outputAddr, i);
    //this ensures that the bundle won't be too big by splitting it up into multiple bundles
    if (bundleSize>=12){
      bundleSize=0;
    }
  } 
}

void doDigitalPullupRead(){
  int bundleSize = 0;
  for(byte i = 0; i < DIGITAL_PINS; i++){
    bundleSize++;
    char outputAddr[8] = "/d/u/xx";
    outputAddr[5] = pinString[i][1];
    outputAddr[6] = pinString[i][2];
    addDigitalPullupRead(outputAddr, i);
    //this ensures that the bundle won't be too big by splitting it up into multiple bundles
    if (bundleSize>=12){
      bundleSize=0;
    }
  } 
}


void doAnalogRead(){
  int bundleSize = 0;
  for(byte i = 0; i < ANALOG_PINS; i++){
    bundleSize++;
    char outputAddr[8] = "/a/i/xx";
    outputAddr[5] = pinString[i][1];
    outputAddr[6] = pinString[i][2];
    addAnalogRead(outputAddr, i);
    //this ensures that the bundle won't be too big by splitting it up into multiple bundles
    if (bundleSize>=12){
      bundleSize=0;
      sendBundle();
    }
  } 
}

void doAnalogPullupRead(){
  int bundleSize = 0;
  for(byte i = 0; i < ANALOG_PINS; i++){
    bundleSize++;
    char outputAddr[8] = "/a/u/xx";
    outputAddr[5] = pinString[i][1];
    outputAddr[6] = pinString[i][2];
    addAnalogPullupRead(outputAddr, i);
    //this ensures that the bundle won't be too big by splitting it up into multiple bundles
    if (bundleSize>=12){
      bundleSize=0;
    }
  } 
}

void pollingMode(){
  sendBundle();
  if (analogReadMode){
    doAnalogRead(); 
    sendBundle();
  }
  if (digitalReadMode){
    doDigitalRead();
    sendBundle();
  }
  if (analogPullupReadMode){
    doAnalogPullupRead(); 
    sendBundle();
  }
  if (digitalPullupReadMode){
    doDigitalPullupRead();
    sendBundle();
  } 
}



