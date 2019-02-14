class tiles {
    //plant*
    //animals**
    char enviroment;

    public:
    tiles();
    ~tiles();
    void changeEnviroment(const char&);
};

class ecosystem {

    int terrainSize;
    int dayOfYear;
    tiles*** terrain;

    void MapGenerator();
    void GenerateRiver();
    void GenerateLake();
    void GenerateHills();
    void GenerateMeadow();

    public:
    ecosystem(const int&, const int&);
    ~ecosystem();
    void RunEcosystem();
};