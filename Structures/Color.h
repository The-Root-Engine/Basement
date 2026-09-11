
struct FColor
{
    
public:
	uint8 R;
	uint8 G;
	uint8 B;
    
    constexpr FColor() = default;
    constexpr FColor(const uint8 InR, const uint8 InG, const uint8 InB) : R(InR), G(InG), B(InB) {}
	
	static const FColor Black;
    static const FColor White;
    static const FColor Gray;
    static const FColor Silver;

    static const FColor Red;
    static const FColor Green;
    static const FColor Blue;

    static const FColor Yellow;
    static const FColor Cyan;
    static const FColor Magenta;

    static const FColor Orange;
    static const FColor Purple;
    static const FColor Turquoise;
};

constexpr FColor FColor::Black     = FColor(0  , 0  , 0  );
constexpr FColor FColor::White     = FColor(255, 255, 255);
constexpr FColor FColor::Gray      = FColor(128, 128, 128);
constexpr FColor FColor::Silver    = FColor(192, 192, 192);
								   
constexpr FColor FColor::Red       = FColor(255, 0  , 0  );
constexpr FColor FColor::Green     = FColor(0  , 255, 0  );
constexpr FColor FColor::Blue      = FColor(0  , 0  , 255);
								   
constexpr FColor FColor::Yellow    = FColor(255, 255, 0  );
constexpr FColor FColor::Cyan      = FColor(0  , 255, 255);
constexpr FColor FColor::Magenta   = FColor(255, 0  , 255);
								   
constexpr FColor FColor::Orange    = FColor(255, 128, 0  );
constexpr FColor FColor::Purple    = FColor(128, 0  , 128);
constexpr FColor FColor::Turquoise = FColor(64 , 224, 208);
