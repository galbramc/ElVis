void Write_Surfids (FILE *fp);
void Load_Surface  (char *name);
void Free_data     (void);
void fillElmt(Element *E, int fac, int felfac);
void GenSurf(Element *E, double *x, double *y, double *z, Curve *curve);

#ifdef EQUIPTS
static double Surf_x[][45] = {
{-1.000000000000, 1.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000,  0.000000000000,  1.000000000000, -1.000000000000,
 0.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000,  -0.333333333333, 0.333333333333,  1.000000000000,
 -1.000000000000, -0.333333333333, 0.333333333333, -1.000000000000, 
 -0.333333333333, -1.000000000000,   0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.5000000,  0.000000000000,  0.500000,  1.000000000000,
 -1.000000000000, -0.500000,  0.0,  0.5000000, -1.000000000000, -0.500000, 
 0.000000000000, -1.000000000000, -0.5000000, -1.000000000000,  0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.60000, -0.200000,  0.20000,  0.600000,  1.000000000000,
 -1.000000000000, -0.600000, -0.200000,  0.200000,  0.600000, -1.000000000000,
 -0.600000, -0.200000,  0.200000, -1.000000000000, -0.600000, -0.2000000,
 -1.000000000000, -0.60000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0}};

static double Surf_y [][45] = {
{-1.000000000000, -1.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000,  0.000000000000, 
 0.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -0.333333333333, -0.333333333333, -0.333333333333,  0.333333333333,
 0.333333333333,   1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -0.5, -0.5, -0.5, -0.,  0.000000000000,  0.0,  0.000000000000,
 0.5,  0.5,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -1.000000000000, -0.6, -0.6, -0.6, -0.6, -0.6, -0.2, -0.2,
 -0.2, -0.2,  0.2,  0.2,  0.2,  0.6,  0.6,  1.000000000000,  0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0}
};

#else

#if 0
static double Surf_x[][45] = {
{-1.000000000000, 1.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000,  0.000000000000,  1.000000000000, -1.000000000000,  
 0.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.468848793471,  0.468848793471,  1.000000000000, 
 -1.000000000000, -0.333333333333,  0.468848793471, -1.000000000000, 
 -0.468848793471, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.654653670708,  0.000000000000,  0.654653670708,  
 1.000000000000, -1.000000000000, -0.525759966481,  0.051519932962,  
 0.654653670708, -1.000000000000, -0.525759966481,  0.000000000000, 
 -1.000000000000, -0.654653670708, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.765055323929, -0.285231516481,  0.285231516481,  
 0.765055323929,  1.000000000000, -1.000000000000, -0.684963697567, 
 -0.178969698014,  0.369927395135,  0.765055323929, -1.000000000000, 
 -0.642060603973, -0.178969698014,  0.285231516481, -1.000000000000, 
 -0.684963697567, -0.285231516481, -1.000000000000, -0.765055323929, 
 -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.830223896279, -0.468848793471,  0.000000000000,  
 0.468848793471,  0.830223896279,  1.000000000000, -1.000000000000, 
 -0.787766142924, -0.380403569720,  0.113819840750,  0.575532285848,  
 0.830223896279, -1.000000000000, -0.733416271030, -0.333333333333,  
 0.113819840750,  0.468848793471, -1.000000000000, -0.733416271030, 
 -0.380403569720,  0.000000000000, -1.000000000000, -0.787766142924, 
 -0.468848793471, -1.000000000000, -0.830223896279, -1.000000000000,  0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{ -1.0000000000000000, -0.8717401485096068, -0.5917001814331426,  
 -0.2092992179024790,  0.2092992179024790,  0.5917001814331426,  
  0.8717401485096068,  1.0000000000000000, -0.9358700742548034,  
 -0.8018438566163038, -0.4434132612743051, -0.0,                 
  0.4434132612743051,  0.8018438566163038,  0.9358700742548034,  
 -0.7958500907165712, -0.5844760044310784, -0.2187879348580840,  
  0.2187879348580840,  0.5844760044310784,  0.7958500907165712,  
 -0.6046496089512394, -0.3433170275438818, -0.0,                 
  0.3433170275438818,  0.6046496089512394, -0.3953503910487606,  
 -0.1410675804263664,  0.1410675804263664,  0.3953503910487606,  
 -0.2041499092834287,  0.0,                 0.2041499092834287,  
 -0.0641299257451966,  0.0641299257451966,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000},

{-1.000000000000, -0.899757995411, -0.677186279511, -0.363117463826,
 0.000000000000,  0.363117463826,  0.677186279511,  0.899757995411, 
 1.000000000000, -1.000000000000, -0.906062419532, -0.639708884004,
 -0.276408013306,  0.108329172035,  0.503800316088,  0.812125946038, 
 0.899757995411, -1.000000000000, -0.864093139099, -0.593316446338,
 -0.218898519168,  0.186614302111,  0.503825806744,  0.677186279511,
 -1.000000000000, -0.831924993989, -0.562196229433, -0.218900197336, 
 0.108325372936,  0.363117463826, -1.000000000000, -0.831923794121,
 -0.593306327609, -0.276407078529, -0.000000000000, -1.000000000000,
 -0.864092199373, -0.639716858100, -0.363117463826, -1.000000000000,
 -0.906062836229, -0.677186279511, -1.000000000000, -0.899757995411,
 -1.000000000000 }};


static double Surf_y [][45] = {
{-1.000000000000, -1.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000,  0.000000000000,  
 0.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -0.468848793471, -0.333333333333, -0.468848793471,  0.468848793471,
 0.468848793471,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -1.000000000000, -0.654653670708, -0.525759966481, -0.525759966481, 
 -0.654653670708,  0.000000000000,  0.051519932962,  0.000000000000,  
 0.654653670708,  0.654653670708,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -1.000000000000, -1.000000000000, -0.765055323929, -0.684963697567,
 -0.642060603973, -0.684963697567, -0.765055323929, -0.285231516481,
 -0.178969698014, -0.178969698014, -0.285231516481,  0.285231516481, 
 0.369927395135,  0.285231516481,  0.765055323929,  0.765055323929, 
 1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -1.000000000000, -1.000000000000, -1.000000000000, -0.830223896279,
 -0.787766142924, -0.733416271030, -0.733416271030, -0.787766142924,
 -0.830223896279, -0.468848793471, -0.380403569720, -0.333333333333,
 -0.380403569720, -0.468848793471,  0.000000000000,  0.113819840750,
 0.113819840750,  0.000000000000,  0.468848793471,  0.575532285848, 
 0.468848793471,  0.830223896279,  0.830223896279,  1.000000000000,  0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.1110762896763000,
  0.1144056871585310,  0.1584563735122294,  0.1809205794068260,
  0.1584563735122294,  0.1144056871585310,  0.1110762896763000,
  0.3535980152394759,  0.4027953322646982,  0.4510310051423650,
  0.4510310051423650,  0.4027953322646982,  0.3535980152394759,
  0.6847669640886771,  0.7755647737800531,  0.8299851607140447,
  0.7755647737800531,  0.6847669640886771,  1.0472838434802000,
  1.1708015832106670,  1.1708015832106670,  1.0472838434802000,
  1.3784527923294010,  1.5032396641348540,  1.3784527923294010,
  1.6209745178925770,  1.6209745178925770,  1.7320508075688770, 
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000,
  0.0000000000000000,  0.0000000000000000,  0.0000000000000000},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -0.899757995411, -0.906063526506, -0.864091432084,
 -0.831921158729, -0.831921158729, -0.864091432084, -0.906063526506,
 -0.899757995411 ,-0.677186279511, -0.639732667645, -0.593297855773,
 -0.562202961663, -0.593297855773, -0.639732667645, -0.677186279511,
 -0.363117463826, -0.276400378947, -0.218903573232, -0.218903573232
 -0.276400378947, -0.363117463826,  0.000000000000,  0.108330872650, 
 0.186612655219,  0.108330872650,  0.000000000000,  0.363117463826, 
 0.503809057473,  0.503809057473,  0.363117463826,  0.677186279511, 
 0.812125672457,  0.677186279511,  0.899757995411,  0.899757995411, 
 1.000000000000}};

#else

static double Surf_x[][45] = {
{-1.000000000000, 1.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000,  0.000000000000,  1.000000000000, -1.000000000000, 
 0.000000000000, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.468848793471,  0.468848793471,  1.000000000000,
 -1.000000000000, -0.333333333333,  0.468848793471, -1.000000000000,
 -0.468848793471, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.654653670708,  0.000000000000,  0.654653670708,
 1.000000000000, -1.000000000000, -0.525759966481,  0.051519932962, 
 0.654653670708, -1.000000000000, -0.525759966481,  0.000000000000,
 -1.000000000000, -0.654653670708, -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.765055323929, -0.285231516481,  0.285231516481, 
 0.765055323929,  1.000000000000, -1.000000000000, -0.684963697567,
 -0.178969698014,  0.369927395135,  0.765055323929, -1.000000000000,
 -0.642060603973, -0.178969698014,  0.285231516481, -1.000000000000,
 -0.684963697567, -0.285231516481, -1.000000000000, -0.765055323929,
 -1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.830223896279, -0.468848793471,  0.000000000000, 
 0.468848793471,  0.830223896279,  1.000000000000, -1.000000000000,
 -0.787766142924, -0.380403569720,  0.113819840750,  0.575532285848, 
 0.830223896279, -1.000000000000, -0.733416271030, -0.333333333333, 
 0.113819840750,  0.468848793471, -1.000000000000, -0.733416271030,
 -0.380403569720,  0.000000000000, -1.000000000000, -0.787766142924,
 -0.468848793471, -1.000000000000, -0.830223896279, -1.000000000000,  0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.871740148510, -0.591700181433, -0.209299217902,
 0.209299217902,  0.591700181433,  0.871740148510,  1.000000000000,
 -1.000000000000, -0.867896010894, -0.534898091176, -0.104454545222, 
 0.351928431372,  0.735791702339,  0.871740148510, -1.000000000000,
 -0.817029997942, -0.479190807090, -0.041614937374,  0.351922010920, 
 0.591700181433, -1.000000000000, -0.791089558460, -0.479192155962,
 -0.104455503372,  0.209299217902, -1.000000000000, -0.817030189661,
 -0.534895028808, -0.209299217902, -1.000000000000, -0.867895824745,
 -0.591700181433, -1.000000000000, -0.871740148510, -1.000000000000,  0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -0.899757995411, -0.677186279511, -0.363117463826, 
 0.000000000000,  0.363117463826,  0.677186279511,  0.899757995411, 
 1.000000000000, -1.000000000000, -0.906062419532, -0.639708884004,
 -0.276408013306,  0.108329172035,  0.503800316088,  0.812125946038, 
 0.899757995411, -1.000000000000, -0.864093139099, -0.593316446338,
 -0.218898519168,  0.186614302111,  0.503825806744,  0.677186279511,
 -1.000000000000, -0.831924993989, -0.562196229433, -0.218900197336, 
 0.108325372936,  0.363117463826, -1.000000000000, -0.831923794121,
 -0.593306327609, -0.276407078529, -0.000000000000, -1.000000000000,
 -0.864092199373, -0.639716858100, -0.363117463826, -1.000000000000,
 -0.906062836229, -0.677186279511, -1.000000000000, -0.899757995411,
 -1.000000000000 }};


static double Surf_y [][45] = {
{-1.000000000000, -1.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000,  0.000000000000, 
 0.000000000000,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -0.468848793471, -0.333333333333, -0.468848793471,  0.468848793471, 
 0.468848793471,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000, 
 -1.000000000000, -0.654653670708, -0.525759966481, -0.525759966481,
 -0.654653670708,  0.000000000000,  0.051519932962,  0.000000000000, 
 0.654653670708,  0.654653670708,  1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -1.000000000000, -0.765055323929, -0.684963697567,
 -0.642060603973, -0.684963697567, -0.765055323929, -0.285231516481,
 -0.178969698014, -0.178969698014, -0.285231516481,  0.285231516481, 
 0.369927395135,  0.285231516481,  0.765055323929,  0.765055323929, 
 1.000000000000,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -1.000000000000, -1.000000000000, -0.830223896279,
 -0.787766142924, -0.733416271030, -0.733416271030, -0.787766142924,
 -0.830223896279, -0.468848793471, -0.380403569720, -0.333333333333,
 -0.380403569720, -0.468848793471,  0.000000000000,  0.113819840750, 
 0.113819840750,  0.000000000000,  0.468848793471,  0.575532285848, 
 0.468848793471,  0.830223896279,  0.830223896279,  1.000000000000,  0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -0.871740148510, -0.867895691444, -0.817030340196, -0.791090909555,
 -0.817030340196, -0.867895691444, -0.871740148510, -0.591700181433,
 -0.534892012977, -0.479194255536, -0.479194255536, -0.534892012977,
 -0.591700181433, -0.209299217902, -0.104454938168, -0.041615688077,
 -0.104454938168, -0.209299217902,  0.209299217902,  0.351925218469, 
 0.351925218469,  0.209299217902,  0.591700181433,  0.735791649490, 
 0.591700181433,  0.871740148510,  0.871740148510,  1.000000000000,  0.0, 0.0,
 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
{-1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -1.000000000000, -1.000000000000, -1.000000000000,
 -1.000000000000, -0.899757995411, -0.906063526506, -0.864091432084,
 -0.831921158729, -0.831921158729, -0.864091432084, -0.906063526506,
 -0.899757995411 ,-0.677186279511, -0.639732667645, -0.593297855773,
 -0.562202961663, -0.593297855773, -0.639732667645, -0.677186279511,
 -0.363117463826, -0.276400378947, -0.218903573232, -0.218903573232
 -0.276400378947, -0.363117463826,  0.000000000000,  0.108330872650, 
 0.186612655219,  0.108330872650,  0.000000000000,  0.363117463826, 
 0.503809057473,  0.503809057473,  0.363117463826,  0.677186279511, 
 0.812125672457,  0.677186279511,  0.899757995411,  0.899757995411, 
 1.000000000000}};
#endif
#endif





