//////////////////////////////////////////////////////////////////////////////////////////////////
#include "DEncryptor2.h"
#include <math.h>

string XOR_Cipher::toBinary(int n) {
    bin = (n%2 == 0 ?"0":"1") + bin;
    if (n / 2 != 0) {
        toBinary(n / 2);
    }
    return bin;
}


string XOR_Cipher::encryptText(string text) {
    string out {};
    string t {};
    // cout << XORwith << endl;

    for (size_t i = 0; i < text.length(); i++) {
        t = toBinary((int) text.at(i));
        cout << text.at(i) <<"  " << t.length() << endl;

        if(t.length() < 7) {
            for(size_t k=0; k<7-t.length(); k++) {
                t = '0' + t;
            }

        }

        for(size_t j = 0; j < 7; j++) {
            if(t.at(j) == XORwith.at(j))
                out += '0';
            else
                out += '1';
        }

        out += '-';
        bin = "";
    }
    return out;
}

int XOR_Cipher::fromBinary(string bin) {
    int out {0};
    int power {0};

    for(int i=6; i>-1; i--) {
        if (bin.at(i) == '1') {
            out += pow(2, power);
        }
        power++;
    }

    // Move to main and uncomment for testing this function
    // cout << C.fromBinary("1000001"); // B
    return out;
}

string XOR_Cipher::decryptText(string text) {
    string out {};
    string t1 {};
    string t2 {};

    for (size_t i = 0; i < text.length(); i++) {
        if(text.at(i) == '-'){
            for(size_t j = 0; j < 7; j++) {
                if(t1.at(j) == XORwith.at(j))
                    t2 += '0';
                else
                    t2 += '1';
            }

            out += fromBinary(t2);
            t1 = ""; t2 = "";
        }
        else
            t1 += text.at(i);
    }
    return out;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
string HillCipher::sanitizeKeyword(string kwrd) {
	int offset = 65;

	if(kwrd.length() > 6) {
		return kwrd.substr(0,6);
	}
	else if (kwrd.length() < 6) {
		for(size_t i; i< 6-kwrd.length(); i++) {
			kwrd += (char) offset;
			offset++;
		}
		return kwrd;
	}
	else {
		return kwrd;
	}
}



int HillCipher::createEncryptMatrix(string keyword) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            encryptMatrix[i][j] = (keyword[k]) % 65;
            k++;
        }
    }

    // Check if determinant != 0
    int determinant {0};
    for(int i = 0; i < 3; i++)
      determinant += (encryptMatrix[0][i] * (encryptMatrix[1][(i+1)%3] * encryptMatrix[2][(i+2)%3] - encryptMatrix[1][(i+2)%3] * encryptMatrix[2][(i+1)%3]));

    if(determinant == 0) {
        cout << "This keyword cannot be used since it does not support the mathematics behind this cipher" << endl;
        return 1;
    }

    // Print out to the console
    cout << "Encrypt Matrix" <<endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            cout << encryptMatrix[i][j] << "\t";
        cout << "\n";
    }
    return 0;
}

int HillCipher::mod26(int n) {
    if(n>=0)
        return n % 26;
    else
        return 26 + (n % 26);
}

int HillCipher::modInverse(int a, int m) {
    a = a%m;
    for (int x=1; x<m; x++)
       if ((a*x) % m == 1)
          return x;
    return 0;
}

void HillCipher::createDecryptMatrix(string keyword) {
    int determinant {0};
    for(int i = 0; i < 3; i++)
      determinant += (encryptMatrix[0][i] * (encryptMatrix[1][(i+1)%3] * encryptMatrix[2][(i+2)%3] - encryptMatrix[1][(i+2)%3] * encryptMatrix[2][(i+1)%3]));

    cout << modInverse(mod26(determinant), 26) << endl;

    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++)
        decryptMatrix[i][j] = mod26(((encryptMatrix[(j+1)%3][(i+1)%3] * encryptMatrix[(j+2)%3][(i+2)%3]) - (encryptMatrix[(j+1)%3][(i+2)%3] * encryptMatrix[(j+2)%3][(i+1)%3])) * determinant);
    }


    // Print out to the console
    cout << "Decrypt Matrix" <<endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            cout << decryptMatrix[i][j] << "\t";
        cout << "\n";
    }

}

string HillCipher::encryptText(string message) {
    int messageVector[3][1] {};
    for (int i = 0; i < 3; i++)
        messageVector[i][0] = (message[i]) % 65;

    int cipherMatrix[3][1] {};

    int x, i, j;
    for (i = 0; i < 3; i++)  {
        for (j = 0; j < 1; j++) {
            cipherMatrix[i][j] = 0;
            for (x = 0; x < 3; x++) {
                cipherMatrix[i][j] += encryptMatrix[i][x] * messageVector[x][j];
            }
            cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
        }
    }

    string cipher{};
    for (int i = 0; i < 3; i++)
        cipher += cipherMatrix[i][0] + 65;

    return cipher;
}

string HillCipher::decryptText(string cipher) {
    int cipherVector[3][1] {};
    for (int i = 0; i < 3; i++)
        cipherVector[i][0] = (cipher[i]) % 65;

    int messageMatrix[3][1] {};

    int x, i, j;
    for (i = 0; i < 3; i++)  {
        for (j = 0; j < 1; j++) {
            messageMatrix[i][j] = 0;
            for (x = 0; x < 3; x++) {
                messageMatrix[i][j] += decryptMatrix[i][x] * cipherVector[x][j];
            }
            messageMatrix[i][j] = messageMatrix[i][j] % 26;
        }
    }

    string message{};
    for (int i = 0; i < 3; i++)
        message += (char) (messageMatrix[i][0] + 65);

    return message;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void TranspositionCipher::setPermutationOrder() {
    if(key.length() == 4) {
        for(uint8_t i=0; i < key.length(); i++) {
            keyMap[key.at(i)] = i;
        }
    }
}

string TranspositionCipher::encryptText(string msg) {
    int row,col,j;
    string cipher = "";

    col = key.length();
    row = msg.length()/col;
    if (msg.length() % col)
        row += 1;

    char matrix[row][col];
    for (int i=0,k=0; i < row; i++) {
        for (int j=0; j<col; j++) {
            if(msg[k] == '\0') {
                matrix[i][j] = '_';
                k++; continue;
            }
            if( isalpha(msg[k]) || msg[k]==' ') {
                matrix[i][j] = msg[k];
                k++;
            }
        }
    }

    for (map<int,int>::iterator ii = keyMap.begin(); ii!=keyMap.end(); ++ii) {
        j=ii->second;
        for (int i=0; i<row; i++) {
            if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
                cipher += matrix[i][j];
        }
    }

    return cipher;
}

string TranspositionCipher::decryptText(string cipher) {
    int col = key.length();
    int row = cipher.length()/col;
    char cipherMat[row][col];

    for (int j=0,k=0; j<col; j++)
        for (int i=0; i<row; i++)
            cipherMat[i][j] = cipher[k++];

    int index = 0;
    for( map<int,int>::iterator ii=keyMap.begin(); ii!=keyMap.end(); ++ii)
        ii->second = index++;

    char decCipher[row][col];
    map<int,int>::iterator ii=keyMap.begin();
    int k = 0;
    for (int l=0,j; key[l]!='\0'; k++) {
        j = keyMap[key[l++]];
        for (int i=0; i<row; i++) {
            decCipher[i][k]=cipherMat[i][j];
        }
    }

    string msg = "";
    for (int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            if(decCipher[i][j] != '_')
                msg += decCipher[i][j];
        }
    }
    return msg;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
string NullCipher::encryptText(string text) {
    string out {};

    srand(time(nullptr));
    for (size_t i = 0; i<text.length(); i++) {
        if (isalpha(text.at(i))) {
            // Generate random from 0-99 and get any word from map of vector
            int any = (int) rand()%100;
            out += (dictonary[toupper(text.at(i))])[any];
        }
        else {
            out += (char) text.at(i);
        }
        out += ' ';
    }
    return out;
}

string NullCipher::decryptText(string text) {
    string out {};
    text = ' ' + text;

    for (size_t i = 0; i<text.length()-2; i++) {
        if (text.at(i) == ' ') {
            out += toupper(text.at(i+1));
            if(text.at(i+2) == ' ') i++;
        }
    }
    return out;
}

// The messy part of NULL cipher!
void NullCipher::generateDictonary() {
    dictonary.insert( make_pair('A', array<string, 100> {"application", "auditor", "absorb", "advice", "authority", "appreciate", "agent", "artist", "allow", "aquarium", "abbey", "abolish", "active", "amuse", "assume", "abortion", "attitude", "accept", "automatic", "article", "arrange", "authorise", "arena", "accountant", "advantage", "ambiguous", "appearance", "aware", "arrest", "attraction", "acquisition", "adoption", "avenue", "answer", "able", "advance", "aloof", "arrow", "analyst", "applied", "abundant", "agency", "adult", "audience", "affinity", "autonomy", "agile", "anticipation", "account", "address", "aloof", "activity", "auditor", "arrange", "assignment", "architect", "aquarium", "adoption", "advocate", "ambiguous", "analysis", "association", "acquaintance", "assembly", "administration", "advertise", "abandon", "appear", "alarm", "arrow", "appointment", "appreciate", "annual", "agency", "arena", "abundant", "absorption", "attachment", "analyst", "apology", "anticipation", "artificial", "addicted", "autonomy", "advertising", "approve", "abbey", "audience", "achievement", "agriculture", "adult", "approval", "alcohol", "arch", "asylum", "adopt", "agony", "abridge", "academy", "appoint"}));
    dictonary.insert( make_pair('B', array<string, 100> {"bitter", "bomber", "benefit", "beginning", "bland", "blind", "bald", "bake", "blame", "base", "bedroom", "back", "birthday", "brain", "bank", "buttocks", "button", "bacon", "beer", "bend", "barrel", "bring", "blank", "banana", "baby", "biology", "bride", "budget", "bloodshed", "betray", "basis", "bowel", "bench", "brush", "blue", "burst", "bishop", "band", "brag", "break", "blackmail", "bean", "borrow", "book", "bathroom", "block", "brick", "bubble", "brilliance", "bulb", "bond", "biography", "bracket", "beard", "butterfly", "bird", "bother", "beach", "bleed", "bathroom", "breeze", "burst", "battlefield", "ball", "beginning", "bridge", "banner", "belong", "band", "biology", "basis", "bank", "blade", "bubble", "baseball", "bang", "belief", "bounce", "break", "banquet", "benefit", "breed", "blue", "boat", "bean", "bury", "basket", "bill", "bench", "blow", "bottle", "bucket", "ballet", "border", "budge", "bulletin", "bomb", "belt", "beer", "boot"}));
    dictonary.insert( make_pair('C', array<string, 100> {"cream", "cherry", "crevice", "creed", "cheek", "complete", "choke", "constellation", "coffee", "column", "chain", "colon", "coverage", "content", "curl", "copyright", "credibility", "ceiling", "crude", "constitutional", "characteristic", "carve", "cassette", "contraction", "clothes", "cast", "country", "cupboard", "cathedral", "compound", "carrot", "carpet", "catch", "cattle", "committee", "coach", "college", "card", "consultation", "chest", "competence", "crack", "commitment", "cinema", "create", "convince", "clinic", "confrontation", "correction", "congress", "certain", "cheek", "core", "cake", "creation", "college", "convince", "collect", "canvas", "compliance", "congress", "confession", "complex", "conscience", "century", "crime", "concrete", "class", "consensus", "coffin", "cabinet", "crash", "ceremony", "concert", "consultation", "collapse", "crackpot", "critical", "cemetery", "charity", "cast", "choke", "charismatic", "common", "current", "chalk", "conservative", "cucumber", "cancel", "crop", "concern", "charge", "column", "cooperate", "conviction", "contract", "constellation", "compound", "chip", "cheese"}));
    dictonary.insert( make_pair('D', array<string, 100> {"dive", "delicate", "delay", "develop", "disagree", "demonstrator", "deteriorate", "distance", "ditch", "dash", "distort", "difference", "delete", "disappear", "designer", "describe", "damn", "divide", "deserve", "despair", "draft", "domestic", "demand", "definition", "detail", "danger", "deny", "desert", "dare", "dominate", "deep", "dismissal", "depart", "demonstrate", "duck", "disagreement", "deprive", "democratic", "drown", "devote", "disorder", "default", "desire", "disturbance", "dimension", "disposition", "debate", "discovery", "deprivation", "decrease", "degree", "decline", "drama", "diplomat", "design", "double", "ditch", "denial", "default", "deck", "dull", "deal", "defend", "disorder", "differ", "digital", "density", "dressing", "death", "disaster", "despair", "disappear", "dictionary", "desk", "definition", "dirty", "debt", "drive", "discuss", "dare", "drown", "display", "delete", "deficit", "demonstration", "detective", "direct", "discover", "dominant", "doll", "doubt", "deliver", "dimension", "disco", "definite", "disagreement", "document", "democratic", "deficiency", "delicate"}));
    dictonary.insert( make_pair('E', array<string, 100> {"edition", "emergency", "estimate", "export", "enhance", "evoke", "expect", "entry", "exchange", "error", "elite", "europe", "elapse", "equinox", "extract", "effect", "electron", "eyebrow", "exploit", "execute", "east", "excavation", "elephant", "extent", "ensure", "exposure", "element", "exercise", "evolution", "excess", "enter", "explode", "eliminate", "economic", "eavesdrop", "elaborate", "entitlement", "easy", "education", "exceed", "economy", "exhibition", "established", "energy", "enlarge", "earthwax", "eternal", "even", "employ", "extraterrestrial", "error", "expression", "earthflax", "endorse", "electronics", "edge", "exaggerate", "eaux", "exposure", "experience", "enter", "executrix", "endure", "embarrassment", "excavation", "exact", "explain", "embark", "essential", "empirical", "evolution", "ethnic", "expectation", "extort", "equation", "effect", "entertain", "expansion", "entry", "excuse", "extend", "emergency", "entertainment", "exceed", "exclusive", "elapse", "extent", "equinox", "exploit", "excess", "employ", "essay", "extinct", "east", "experienced", "engagement", "executive", "ecstasy", "exile", "exercise"}));
    dictonary.insert( make_pair('F', array<string, 100> {"freedom", "feather", "fortune", "feel", "finance", "fragrant", "formula", "formation", "faithful", "freighter", "floor", "flesh", "flush", "failure", "find", "forum", "forge", "farewell", "fraud", "foster", "federation", "false", "football", "foreigner", "first", "factor", "flatware", "flock", "fraction", "fragment", "form", "fund", "favourite", "fitness", "front", "fisherman", "fill", "figure", "feature", "freckle", "flow", "fever", "flourish", "feed", "frozen", "finish", "fireplace", "fluctuation", "forward", "fine", "fraction", "fragrant", "filter", "flood", "fair", "frame", "forestry", "fling", "flow", "find", "formulate", "flesh", "football", "fossil", "fast", "freshman", "friend", "funeral", "feather", "friendly", "fiction", "folk", "failure", "factor", "fire", "forecast", "flawed", "feminist", "fill", "follow", "forge", "fabricate", "fraud", "feminine", "fibre", "frighten", "floor", "flight", "frozen", "flavor", "faint", "fairy", "flower", "feeling", "fail", "favor", "firsthand", "faithful", "fluctuation", "favour"}));
    dictonary.insert( make_pair('G', array<string, 100> {"green", "glass", "grip", "ground", "gradual", "glasses", "garbage", "gallon", "grind", "guerrilla", "grimace", "glance", "gesture", "guideline", "guilt", "glory", "generation", "gear", "graphic", "gravel", "girlfriend", "gate", "good", "groan", "gallery", "grand", "grave", "goalkeeper", "grandfather", "garlic", "ghostwriter", "graze", "gutter", "grandmother", "general", "garage", "goat", "gaffe", "guarantee", "gown", "grateful", "gregarious", "glue", "grounds", "genuine", "glacier", "genetic", "gasp", "guard", "gene", "gear", "grounds", "glasses", "gate", "garage", "game", "goat", "ground", "gift", "ghost", "glory", "guess", "good", "gossip", "glue", "greet", "glide", "grief", "grand", "guide", "grateful", "generate", "grass", "garlic", "gown", "gallon", "girl", "grimace", "gaffe", "glare", "glimpse", "groan", "guerrilla", "gradient", "genuine", "guard", "gold", "gallery", "gregarious", "global", "grip", "grandmother", "glance", "gutter", "ghostwriter", "general", "glow", "gradual", "guideline", "glacier"}));
    dictonary.insert( make_pair('H', array<string, 100> {"habit", "harmony", "harvest", "honest", "hierarchy", "hope", "hunter", "horoscope", "herb", "haircut", "husband", "hall", "helmet", "hypnothize", "hurl", "happen", "heart", "helpless", "house", "hardware", "hospital", "herd", "hypothesis", "headquarters", "hide", "hover", "hostile", "hobby", "horizon", "homosexual", "hotdog", "heal", "head", "hero", "health", "humor", "hair", "horror", "horse", "harsh", "honor", "halt", "have", "height", "host", "hypothesize", "hospitality", "hate", "holiday", "hardship", "hostility", "hesitate", "heaven", "housewife", "halt", "hypothesis", "hobby", "horse", "headquarters", "hall", "harm", "history", "housing", "holiday", "height", "herb", "heroin", "humor", "hospitality", "help", "harsh", "hurt", "haunt", "hostile", "habit", "husband", "hair", "hill", "hear", "hover", "head", "helicopter", "happen", "huge", "hostage", "hierarchy", "have", "host", "heel", "hemisphere", "health", "homosexual", "horn", "handy", "hardship", "hour", "heal", "hotdog", "horoscope", "hiccup"}));
    dictonary.insert( make_pair('I', array<string, 100> {"insistence", "intensify", "investigation", "inquiry", "indication", "insight", "integrated", "idea", "instrument", "interest", "illusion", "improve", "inside", "intelligence", "interactive", "instruction", "instal", "illustrate", "insure", "introduce", "insert", "index", "inspector", "ignore", "indoor", "inspiration", "instinct", "implication", "invisible", "inhabitant", "imperial", "influence", "infect", "industry", "indirect", "important", "infinite", "innocent", "item", "initiative", "invasion", "information", "irony", "introduction", "investment", "implicit", "inflate", "ignite", "interface", "impress", "irony", "impulse", "incapable", "inch", "inquiry", "integrated", "issue", "indoor", "invite", "infrastructure", "import", "insure", "inspector", "idea", "inspiration", "influence", "incredible", "interest", "intervention", "interrupt", "ideology", "indirect", "include", "invasion", "intermediate", "institution", "inspire", "inhibition", "imperial", "ivory", "inject", "item", "identity", "inappropriate", "instruction", "ignorant", "industry", "imagine", "install", "interface", "impound", "intensify", "initiative", "improve", "implication", "ignite", "insurance", "insist", "increase", "identification"}));
    dictonary.insert( make_pair('J', array<string, 100> {"junior", "jury", "joke", "jam", "judge", "jest", "jacket", "job", "judgment", "justice", "journal", "jurisdiction", "jet", "jelly", "joint", "jealous", "judicial", "justify", "joystick", "jail", "jaw", "jungle", "jewel", "jump", "just", "jockey", "joy", "junior", "jockey", "jet", "justify", "jury", "jump", "jail", "jungle", "jimmy", "just", "judge", "jewel", "joystick", "judicial", "journal", "job", "justice", "joke", "jacket", "jelly", "jest", "jealous", "jam", "joint", "jaw", "judgment", "jockey", "jump", "joke", "jealous", "jelly", "junior", "justify", "judicial", "judgment", "job", "jewel", "jest", "jungle", "joint", "judge", "jam", "jacket", "jack", "justice", "joystick", "joy", "jail", "jet", "just", "jury", "justice", "jurisdiction", "jacket", "jungle", "joystick", "justify", "jealous", "junior", "jockey", "justify", "joystick", "judge", "jacket", "just", "justice", "jealous", "journal", "joint", "jewel", "jockey", "jurisdiction", "jury"}));
    dictonary.insert( make_pair('K', array<string, 100> {"kick", "keymap", "kill", "knife", "knit", "knee", "kettle", "king", "keep", "kinship", "kidnap", "kidney", "know", "knowledge", "kitchen", "knock", "killer", "kneel", "knot", "kneel", "king", "kidney", "keep", "know", "kill", "kitchen", "kinship", "knee", "knife", "kidnap", "key", "kit", "knowledge", "knock", "kettle", "killer", "kick", "knot", "knit", "kid", "kneel", "kit", "kill", "key", "kitchen", "killer", "kidney", "knock", "kick", "knife", "knot", "knit", "kettle", "knowledge", "knee", "know", "king", "keep", "kidnap", "kinship", "know", "knock", "kidney", "kneel", "keep", "kettle", "kid", "king", "knowledge", "knot", "key", "kick", "kidnap", "kinship", "kitchen", "kit", "killer", "knife", "kill", "knee", "knit", "kinship", "killer", "knowledge", "kidney", "kit", "kidnap", "know", "knife", "kick", "knot", "keep", "kid", "knock", "key", "kettle", "kneel", "knee", "king", "knit"}));
    dictonary.insert( make_pair('L', array<string, 100> {"lunch", "land", "learn", "law", "left", "loud", "lineage", "low", "leg", "lifestyle", "liberty", "licence", "lace", "line", "layer", "lemon", "lesson", "leaflet", "loyalty", "light", "lay", "lighter", "laser", "letter", "lamp", "lend", "loose", "lick", "log", "lip", "loop", "location", "legend", "laboratory", "lost", "lake", "landowner", "look", "leftovers", "leaf", "ladder", "lazy", "leash", "launch", "literature", "listen", "lobby", "live", "loss", "lung", "lay", "look", "last", "likely", "lighter", "licence", "learn", "lake", "ladder", "length", "lawyer", "list", "liberty", "license", "lace", "log", "lamb", "lecture", "loose", "literature", "lease", "lifestyle", "leftovers", "lonely", "lend", "lump", "latest", "leash", "locate", "loss", "lean", "lazy", "lock", "lodge", "leaf", "leadership", "looting", "leaflet", "limit", "leave", "leader", "love", "loan", "legislation", "left", "link", "load", "lung", "lineage", "lick"}));
    dictonary.insert( make_pair('M', array<string, 100> {"magnetic", "morsel", "miscarriage", "manager", "multiply", "mild", "museum", "monstrous", "mountain", "motorist", "multimedia", "myth", "maze", "mercy", "microphone", "minimum", "my", "mouse", "movement", "manual", "material", "miner", "meaning", "member", "means", "mouth", "medieval", "mutual", "memory", "mud", "monk", "measure", "marble", "mature", "marsh", "map", "mirror", "moral", "master", "mayor", "menu", "market", "mislead", "mine", "make", "mean", "mass", "mix", "moon", "manufacture", "midnight", "migration", "minor", "mechanical", "marsh", "maximum", "missile", "mourning", "multimedia", "march", "mole", "metal", "master", "model", "man", "mud", "marine", "muscle", "main", "miner", "mood", "maze", "maid", "museum", "morsel", "minimum", "mainstream", "mosquito", "monk", "market", "management", "microphone", "mouse", "margin", "monarch", "material", "meeting", "move", "manage", "memorandum", "money", "mistreat", "movie", "moving", "medieval", "miracle", "mother", "meadow", "myth", "motorist"}));
    dictonary.insert( make_pair('N', array<string, 100> {"node", "no", "normal", "norm", "notion", "neck", "night", "nuclear", "nightmare", "name", "notebook", "negative", "national", "negligence", "net", "native", "nonsense", "novel", "nominate", "nuance", "needle", "neglect", "nap", "negotiation", "nest", "nursery", "notorious", "nationalist", "number", "note", "neighborhood", "nail", "nature", "nervous", "network", "nerve", "need", "neutral", "new", "narrow", "news", "necklace", "nut", "noble", "notice", "nomination", "north", "neighbour", "navy", "nose", "nightmare", "noble", "normal", "net", "need", "nail", "new", "night", "narrow", "nationalism", "news", "nursery", "needle", "notorious", "north", "nest", "navy", "nuance", "native", "necklace", "novel", "note", "nationalist", "node", "norm", "neglect", "negative", "number", "noise", "name", "neutral", "no", "nose", "nature", "nut", "network", "nervous", "neck", "nun", "notebook", "neighborhood", "nonsense", "notice", "neighbour", "national", "nominate", "nonremittal", "nuclear", "nerve", "nomination"}));
    dictonary.insert( make_pair('O', array<string, 100> {"occupation", "onion", "orange", "oppose", "output", "oil", "officer", "oven", "owl", "owe", "offer", "outside", "offensive", "orthodox", "occupy", "overwhelm", "owner", "offend", "obese", "obstacle", "observation", "of", "overlook", "oral", "on", "objective", "overview", "official", "opposition", "or", "obligation", "opera", "observer", "orgy", "overall", "offspring", "origin", "operation", "opponent", "outlet", "object", "occasion", "other", "obscure", "oh", "overcharge", "orbit", "overeat", "oak", "office", "ordinary", "offspring", "opposed", "observation", "oven", "output", "orientation", "outer", "operational", "ostracize", "oh", "oak", "orbit", "original", "offer", "opinion", "origin", "oral", "oil", "observer", "overview", "organ", "option", "offense", "other", "of", "obese", "offend", "old", "owner", "offset", "opera", "order", "onion", "orange", "oppose", "overlook", "occasion", "overwhelm", "obstacle", "object", "orthodox", "operation", "organize", "overall", "opponent", "opposite", "or", "organisation", "orchestra"}));
    dictonary.insert( make_pair('P', array<string, 100> {"progress", "preach", "perform", "perception", "pilot", "pill", "presidential", "physics", "peanut", "premium", "possession", "particle", "pay", "poor", "privilege", "poetry", "plug", "powder", "purpose", "professor", "position", "peace", "pavement", "pierce", "plaster", "philosophy", "pig", "paradox", "paralyzed", "permanent", "plot", "profit", "pension", "pardon", "process", "photograph", "proud", "pass", "preoccupation", "publication", "pipe", "plaintiff", "product", "penalty", "persist", "pawn", "property", "page", "parking", "profound", "progress", "preach", "perform", "perception", "pilot", "pill", "presidential", "physics", "peanut", "premium", "possession", "particle", "pay", "poor", "privilege", "poetry", "plug", "powder", "purpose", "professor", "position", "peace", "pavement", "pierce", "plaster", "philosophy", "pig", "paradox", "paralyzed", "permanent", "plot", "profit", "pension", "pardon", "process", "photograph", "proud", "pass", "preoccupation", "publication", "pipe", "plaintiff", "product", "penalty", "persist", "pawn", "property", "page", "parking", "profound"}));
    dictonary.insert( make_pair('Q', array<string, 100> {"qualified", "quarter", "question", "queue", "quantity", "quest", "queen", "qualification", "quote", "quarrel", "quit", "quaint", "quota", "quiet", "quality", "quotation", "qualify", "quota", "qualified", "quality", "quote", "quotation", "quarrel", "queen", "quiet", "quantity", "queue", "quest", "qualified", "quarter", "quit", "quaint", "question", "qualify", "question", "quality", "quit", "qualification", "quota", "queen", "quantity", "quotation", "qualify", "quarrel", "quaint", "quote", "quiet", "quarter", "qualified", "queue", "quest", "quality", "quotation", "queue", "quota", "quantity", "quiet", "quarrel", "qualify", "quit", "quill", "quaint", "question", "queen", "quest", "quote", "quarter", "quarrel", "queue", "qualified", "quarter", "quotation", "qualification", "quote", "question", "qualify", "queen", "quill", "quantity", "quota", "quest", "quit", "quality", "quaint", "quiet", "quaint", "question", "queen", "quest", "quote", "quarter", "quarrel", "queue", "qualified", "quarter", "quotation", "quote", "quarter", "qualified", "quack"}));
    dictonary.insert( make_pair('R', array<string, 100> {"random", "referral", "retailer", "reflection", "reader", "replacement", "ratio", "radiation", "recession", "requirement", "rib", "range", "rack", "repetition", "remark", "recover", "reference", "redeem", "right", "resist", "relevance", "responsibility", "red", "restaurant", "railroad", "revenge", "report", "relative", "repeat", "regulation", "related", "rabbit", "rumor", "remedy", "researcher", "reckless", "rebellion", "reptile", "rainbow", "reflect", "recommend", "result", "retirement", "reason", "reinforce", "reach", "reward", "recognize", "rugby", "relinquish", "route", "referral", "recovery", "ratio", "relevance", "real", "reaction", "reverse", "rotten", "rock", "revive", "reward", "rack", "resign", "red", "racism", "rebellion", "remunerate", "rank", "reliable", "rear", "rubbish", "repeat", "ready", "recover", "rebel", "refund", "retreat", "range", "recession", "reproduction", "reactor", "rest", "reinforce", "remain", "relationship", "reception", "ritual", "river", "right", "revival", "related", "rainbow", "reign", "ribbon", "rub", "retirement", "reasonable", "repetition", "rain"}));
    dictonary.insert( make_pair('S', array<string, 100> {"situation", "season", "spokesperson", "second", "sketch", "sit", "sphere", "save", "say", "strikebreaker", "size", "sin", "sensitivity", "suitcase", "sailor", "scramble", "speculate", "sickness", "slap", "sport", "stable", "silence", "south", "system", "slant", "struggle", "symbol", "sample", "square", "spot", "shallow", "soil", "sock", "storm", "satellite", "separate", "summer", "story", "swear", "sticky", "suspect", "sensation", "secular", "settlement", "statement", "seal", "systematic", "spend", "silk", "self", "shortage", "story", "spread", "sector", "skip", "sister", "section", "smile", "sin", "straw", "scholar", "score", "stable", "supplementary", "straight", "scrape", "slogan", "similar", "sensitivity", "shoot", "swarm", "slime", "safe", "swipe", "spot", "shoulder", "suffering", "so", "slump", "stride", "salesperson", "sleep", "symbol", "shot", "soprano", "shout", "stroll", "staircase", "spirit", "solid", "sting", "superior", "stay", "spider", "stamp", "summary", "specimen", "species", "screen", "string"}));
    dictonary.insert( make_pair('T', array<string, 100> {"temple", "treat", "thin", "toll", "thoughtful", "tactic", "tasty", "tail", "tycoon", "twitch", "transform", "tread", "throne", "tell", "transmission", "trust", "trait", "terrify", "torch", "triangle", "traction", "take", "tidy", "twilight", "traffic", "treaty", "tolerate", "thank", "thumb", "trustee", "theater", "turkey", "talented", "trainer", "try", "theorist", "trace", "thick", "tray", "tiger", "television", "therapist", "thinker", "tumble", "trance", "topple", "tournament", "table", "to", "toss", "tasty", "team", "transfer", "tease", "transport", "trap", "tournament", "tough", "tick", "tooth", "threat", "top", "tell", "twilight", "tank", "throat", "topple", "thrust", "temperature", "tax", "tower", "temple", "taste", "ton", "thirsty", "transaction", "tidy", "tail", "theorist", "thought", "table", "trouser", "tongue", "thanks", "talkative", "treat", "tumble", "true", "theft", "tune", "tradition", "terms", "tempt", "tragedy", "testify", "talk", "torch", "tactic", "torture", "twin"}));
    dictonary.insert( make_pair('U', array<string, 100> {"urgency", "upset", "unrest", "uncle", "understand", "urge", "use", "useful", "uncertainty", "umbrella", "unlike", "update", "unanimous", "undress", "unique", "unfair", "unlikely", "union", "unaware", "unfortunate", "uniform", "unit", "unpleasant", "user", "urine", "undermine", "unity", "unlawful", "undertake", "utter", "understand", "utter", "upset", "unique", "unanimous", "unpleasant", "useful", "unaware", "uncertainty", "undertake", "us", "urine", "understand", "use", "underline", "urgency", "urge", "uniform", "update", "undress", "user", "unfortunate", "unlikely", "uncle", "umbrella", "unlike", "undermine", "unlawful", "unrest", "union", "up", "unfair", "unit", "unity", "unpleasant", "urge", "utter", "user", "update", "unique", "understand", "us", "unlikely", "up", "unlawful", "uniform", "unanimous", "union", "unaware", "use", "unit", "underline", "umbrella", "understand", "urgency", "undress", "unfair", "upset", "undermine", "unity", "undertake", "uncertainty", "unlike", "unfortunate", "useful", "urine", "uncle", "unrest", "unique", "use"}));
    dictonary.insert( make_pair('V', array<string, 100> {"vacuum" ,"video" ,"value" ,"vein" ,"virgin" ,"vigorous" ,"veteran" ,"viable" ,"voucher" ,"venture" ,"visit" ,"velvet" ,"variant" ,"victory" ,"voice" ,"valid" ,"volcano" ,"visual" ,"vain" ,"village" ,"verdict" ,"variety" ,"voter" ,"vague" ,"vegetable" ,"voyage" ,"vote" ,"venus" ,"vat" ,"vessel" ,"virus" ,"vegetation" ,"version" ,"vehicle" ,"variable" ,"visible" ,"variation" ,"vertical" ,"veil" ,"van" ,"volunteer" ,"virtue" ,"vegetarian" ,"violation" ,"valley" ,"volume" ,"view" ,"vision" ,"veil" ,"voucher" ,"vehicle" ,"vessel" ,"volunteer" ,"visible" ,"volcano" ,"vain" ,"video" ,"van" ,"verdict" ,"vigorous" ,"violation" ,"vertical" ,"virus" ,"variable" ,"village" ,"visual" ,"venture" ,"vegetable" ,"voter" ,"velvet" ,"variant" ,"vegetarian" ,"virtue" ,"volume" ,"vision" ,"visit" ,"valid" ,"view" ,"virgin" ,"voyage" ,"vegetation" ,"valley" ,"viable" ,"vat" ,"vote" ,"variation" ,"veteran" ,"victory" ,"venus" ,"variety" ,"version" ,"vase" ,"voice" ,"vague" ,"vein" ,"value" ,"video" ,"valid" ,"variety" ,"venue"}));
    dictonary.insert( make_pair('W', array<string, 100> {"writer", "water", "wagon", "wheat", "waterfall", "withdrawal", "waste", "wander", "whisper", "ward", "west", "work", "wine", "warn", "widen", "waiter", "wriggle", "willpower", "welfare", "weapon", "wing", "wardrobe", "wrong", "weed", "weave", "wheel", "window", "weight", "wear", "width", "wild", "wonder", "week", "winter", "weigh", "watch", "wave", "wall", "warm", "wilderness", "worm", "white", "word", "warning", "well", "woman", "workshop", "weak", "wisecrack", "wording", "worker", "whole", "welfare", "want", "winner", "witch", "way", "wind", "wrist", "weed", "wardrobe", "wrong", "word", "wave", "wisecrack", "wrap", "week", "wing", "world", "whisper", "warrant", "wash", "withdrawal", "warm", "wealth", "write", "welcome", "woman", "willpower", "writer", "weigh", "wedding", "we", "wagon", "whip", "workshop", "warning", "wine", "withdraw", "wait", "wheat", "weakness", "width", "worry", "wage", "walk", "wander", "wild", "war", "wound"}));
    dictonary.insert( make_pair('X', array<string, 100> {"xenogamies", "xenoblasts", "xenocrysts", "xenophobic", "xenophiles", "xenophobes", "xenophobia", "xenotropic", "xerodermae", "xerodermas", "xeriscapes", "xerophytes", "xerophytic", "xanthomat", "xenograft", "xylophone", "xeroderma", "xenophobe", "xenophile", "xenocryst", "xylograph", "xenoblast", "xerophyte", "xeroseres", "xerophile", "xerophily", "xenogenic", "xenoliths", "xenopuses", "xeriscape", "xerically", "xanthones", "xanthomas", "xanthines", "xanthenes", "xantheins", "xanthates", "xylocarps", "xylidine", "xanthine", "xenolith", "xanthoma", "xanthate", "xanthene", "xenogamy", "xylidine", "xylotomy", "xerosere", "xanthous", "xanthone", "xanthein", "xanthins", "xanthans", "xeroxing", "xenogeny", "xiphoids", "xylidins", "xylitols", "xylocar", "xenopus", "xylitol", "xerosis", "xiphoid", "xerarch", "xanthic", "xanthin", "xanthan", "xerotic", "xeroses", "xeroxed", "xeroxes", "xylenes", "xylidin", "xysters", "xylose", "xylene", "xylose", "xystus", "xyster", "xyloid", "xylols", "xylems", "xylans", "xylyls", "xebecs", "xenial", "xenias", "xenon", "xylan", "xenon", "xenia", "xebec", "xylem", "xeric", "xylol", "xysts", "xysti", "xylyl", "xenic", "xerox"}));
    dictonary.insert( make_pair('Y', array<string, 100> {"young", "youth", "yield", "yours", "yacht", "yeast", "yahoo", "yummy", "yikes", "yucky", "yapon", "yards", "yanks", "yauds", "yauld", "yaups", "yawed", "yawey", "yawls", "yawns", "yarns", "yacks", "yaffs", "yager", "yagis", "yerks", "yetis", "yeses", "yetts", "yeuks", "yeuky", "years", "yechs", "yechy", "yecch", "yeggs", "yelps", "yells", "yelks", "yeans", "yeahs", "yclad", "yawps", "yowie", "yowed", "yowes", "yowls", "yoked", "yokes", "yolks", "yolky", "yomim", "yocks", "yodle", "yodhs", "yogas", "yogee", "yoghs", "yogic", "yogin", "yogis", "ylems", "yipes", "yukky", "yucks", "yugas", "yules", "your", "year", "yeah", "yard", "yarn", "yuan", "yoga", "yell", "yoke", "yawn", "yolk", "yank", "yore", "yogi", "yuck", "yelp", "yagi", "yeti", "yurt", "yoni", "yawl", "yawp", "yups", "yuga", "yelk", "yeuk", "yews", "yens", "yeps", "yerk", "yays", "yaps", "yes"}));
    dictonary.insert( make_pair('Z', array<string, 100> {"zacaton", "zaddick", "zaffars", "zaffirs", "zagging", "zamarra", "zanyish", "zapateo", "zappers", "zapping", "zaptieh", "zombify", "zonally", "zonated", "zoogeny", "zooming", "zooning", "zygomas", "zygoses", "zygosis", "zygotes", "zygotic", "zymases", "zymogen", "zymosan", "zymosis", "zappy", "zarfs", "zaxes", "zeals", "zebra", "zebus", "zeins", "zerks", "zeros", "zests", "zesty", "zetas", "zibet", "zilch", "zills", "zincs", "zincy", "zineb", "zines", "zings", "zippy", "ziram", "zitis", "zizit", "zlote", "zloty", "zoeae", "zoeal", "zoeas", "zombi", "zonae", "zonal", "zoned", "zoner", "zones", "zonks", "zooey", "zooid", "zooks", "zooms", "zoons", "zooty", "zoril", "zoris", "zouks", "zowie", "zuzim", "zany", "zaps", "zeal", "zebu", "zees", "zein", "zeks", "zeps", "zerk", "zero", "zest", "zeta", "zigs", "zill", "zinc", "zine", "zing", "zins", "zoic", "zona", "zone", "zonk", "zoom", "zoos", "zyme", "zoo", "zeta"}));
}
///////////////////////////////////////////////////////////////////////////////////////////////////
