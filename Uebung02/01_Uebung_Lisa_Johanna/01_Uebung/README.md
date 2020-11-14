Bioinformatik I - Übung 1
=========================

Dieses Codegerüst soll Ihnen als Grundlage für das Erstellen einer generischen Sequenzklasse
dienen. Die Idee hinter dieser Klasse ist, eine einzige Implementierung der Sequenzlogik
zu schreiben, die eigentlichen Buchstaben der Sequenz jedoch austauschbar zu machen.

Bauen des Codegerüsts
---------------------
*Diese Anleitung bezieht sich auf das Bauen auf den CIP Rechnern der Bioinformatik. Sollten
Sie die Übungen auf einem eigenen Rechner bearbeiten wollen, bieten wir dafür **keine** Unterstützung an!*

Bevor Sie das Codegerüst ohne Fehler bauen können, benötigen Sie eine Leerimplementierung aller Klassen,
d.h. Sie müssen alle fehlenden cpp-Dateien ergänzen. Sehen Sie sich dazu CMakeLists.txt an.

Das Codegerüst verwendet das CMake Buildsystem, welches es vereinfacht C++ Code
zu kompilieren. Sie können das Codegerüst wie folgt erstellen:

 1. Legen Sie im Ordner in der sich diese README.md befindet einen Ordner `build` an:
```
mkdir build
```

 2. Wechseln sie in den neu erstellten Ordner hinein:
```
cd build
```

 3. Rufen Sie dann CMake auf:
```
cmake ..
```

 4. Nun können Sie den Code mittels make erstellen:
```
make -j 8
```
 Die Zahl hinter `-j` gibt die Anzahl an Prozessorkernen an, die
 zum Erstellen des Codes verwendet werden sollen.
 Ihre Ausführbare Datei liegt nun direkt im `build` Ordner.

### Bauen auf eigenen Systemen
 * Überlegen Sie sich ob sie nicht per SSH arbeiten möchten.
   Via:
```
ssh username@bioXX.studcs.uni-sb.de
```
   können Sie sich auf den CIP Rechnern einloggen. (Hierbei `XX` durch eine
   Zahl zwischen 01-22 und `username` durch Ihren Benutzernamen ersetzen.)
   Unter Windows müssen Sie dazu einen SSH Client wie z.B.
   [Putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) installieren.
 * Falls Sie eine funktionierende Entwicklungsumgebung besitzen können Sie
   CMake folgendermaßen aufrufen:
```
cmake .. -DUSE_CIPS=OFF -DGTEST_SRC_DIR=/path/to/googletest
```

Ausführung Ihrer Anwendung
--------------------------
Um Ihre `convert` Anwendung auszuführen, müssen Sie diese wie oben
beschrieben gebaut haben. Danach können Sie die Anwendung vom
`build` Ordner aus mittels:
```
./convert input_file_name output_file_name
```
ausführen.

Ausführung der Unittests
------------------------
Um Ihre Unittests auszuführen, tippen Sie:
```
make test
```
Einzelne Tests (z.B. für Sequence) können vom `build` Ordner aus Sie mittels:
```
./test/Sequence_test
```
ausführen.

Hinzufügen eigenen Codes
------------------------
Um eigene Dateien zu ihrem Projekt hinzuzufügen, müssen Sie die CMakeLists.txt Dateien
bearbeiten. In der CMakeLists.txt im Verzeichnis dieser README.md können Sie Dateien zum
`add_library` Aufruf hinzufügen.

Ihre Unittests können Sie am Ende der Datei `test/CMakeLists.txt` hinzufügen.
Unittests müssen unter Zurhilfenahme der Google Test Bibliothek geschrieben werden.
Die Dokumentation hierzu finden sie [hier](https://code.google.com/p/googletest/wiki/V1_7_Primer).

Implementierung
---------------
Dies wird wie folgt erreicht:

```
template<typename Alphabet>
class Sequence {
	// Klassendefinition hier
};

class DNA {
public:
	// Zulässige Buchstaben
	enum class Characters { A, G, T, C };

	// Methoden zur Konvertierung
	static char toChar(Characters c);
	static Characters toChar(char c);
};

class RNA {
public:
	// Zulässige Buchstaben
	enum class Characters { A, G, U, C };

	// Methoden zur Konvertierung
	static char toChar(Characters c);
	static Characters toChar(char c);
};

// Wir können nun eine DNA Sequenz durch
// Einsetzen des richtigen Templateparameters erzeugen:
Sequence<DNA> sequence = Sequence<DNA>::fromString("AGTC");
```

Beachten Sie, das weder DNA noch RNA in irgendeiner Weise von
einer gemeinsamen Basisklasse erben. Sie implementieren jedoch
Funktionen mit identischer Signatur (toChar, toCharacter) und definieren einen Typen
mit dem selben Namen (Characters). Template Programmierung verlässt
sich daher darauf, dass die Parameter eine vom Programmierer bestimmte
Konvention einhalten. Ist dies nicht erfüllt, schlägt die Kompilation
mit mehr oder weniger aussagekräftigen Fehlermeldungen fehl.

Des Weitern soll die Sequence Klasse die Ein- und Ausgabe in diversen
Formaten ermöglichen. Da leider pro Klasse nur ein Ein- und ein
Ausgabeoperator definiert werden kann, müssen wir uns eines kleinen
Tricks bedienen: Wir verpacken eine Sequence Instanz, in eine
Hilfsklasse, welchen einen entsprechend überladenen Ein-/Ausgabeoperator
anbietet.

Konkret ist dies folgendermaßen implementiert:

```
// Dies ist die Hilfsklasse, welche sich um das Einlesen
// einer DNA Sequenz im 2Bit Format kümmert.
class Sequence2BitReader
{
  public:
	// Ein Konstruktor der einfach die übergebene Sequence
	// speichert.
	explicit Sequence2BitReader(Sequence<DNA>& seq);

	// Ein globaler Inputoperator.
	// Die RValue-Referenz (&&) hinter Sequence2BitReader ist nötig,
	// damit die Funktion from2Bit verwendet werden kann.
	// Hier kann diese RValue-eferenz wie eine gewöhnliche Referenz
	// verwendet werden.
	friend std::istream& operator>>(std::istream&, Sequence2BitReader&&);
};

Sequence2BitReader from2Bit(Sequence<DNA>&);
```

Dieser Code kann folgendermaßen verwendet werden:
```
Sequence<DNA> seq;

std::ifstream("some_file.2bit");
input_stream >> from2Bit(seq);
```

###Beachten Sie Folgendes:

 * Die SequenceFastaReader/Writer Klassen sind ebenfalls Templates, die
   mit einem Alphabet parametrisiert werden.
 * Schreiben Sie Ihren Code auch im Hinblick auch mögliche, falsche Eingaben.
   Hierfür sind bereits die Exceptions `InvalidCharacter` und `ParsingException`
   vordefiniert.
 * Template Code *muss* in einer Headerdatei implementiert werden. Implementieren
   Sie Templates nur dann in .cpp Dateien, wenn Sie genau wissen was Sie tun.
 * Für die Implementierung dieses Codes ist *kein einziger* Aufruf von new/delete
   nötig. Ebenso benötigen Sie keine Smart Pointer.

