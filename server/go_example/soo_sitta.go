package main
 
import (
    "fmt"
    "html"
    "log"
	"net/http/httputil"
	"net/http"
	"encoding/json"
)
 
type test_struct struct {
	username string
	password string
}

func main() {
 	http.HandleFunc("/", Index)
	http.HandleFunc("/perse", Perse)
	http.HandleFunc("/pesakond", Pesakond)
    log.Fatal(http.ListenAndServe(":8080", nil))
}
 
func Index(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Söö sitta, %q!", html.EscapeString(r.URL.Path))
}

func Perse(w http.ResponseWriter, r *http.Request) {
	fmt.Fprintf(w, "Sööge perse, idiiot!", html.EscapeString(r.URL.Path))
}

func Pesakond(w http.ResponseWriter, req *http.Request) {
	requestDump, err := httputil.DumpRequest(req, true)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(string(requestDump))

    decoder := json.NewDecoder(req.Body)
    var t test_struct
    errDecode := decoder.Decode(&t)
    if errDecode != nil {
        panic(errDecode)
	}

	fmt.Fprintf(w, "Parsed %q %q", t.username, t.password)
}