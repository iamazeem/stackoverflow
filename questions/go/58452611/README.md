## Go: How is a Cobra Flag of type `StringToStringVar` access using Viper?

### Key/Value Pairs as Command Line Arguments

Link: https://stackoverflow.com/questions/58452611/

## Question (Asked by https://stackoverflow.com/users/783726/)

I am trying to develop an application in Go that accepts inputs on the command line as a string of key value pairs. To do this I am using `StrngToStringVar` from the Cobra library.

I am also using Viper to bind these flags to configuration, however whatever value I put it I do not seem to be able to get it from Viper.

This is the code

    package main
    
    import (
    	"fmt"
    
    	"github.com/spf13/cobra"
    	"github.com/spf13/viper"
    
    	"github.com/davecgh/go-spew/spew"
    )
    
    func main() {
    	var items map[string]string
    	var name string
    
    	rootCmd := &cobra.Command{
    		Use:   "cobra",
    		Short: "Test options on the command line",
    		Long:  ``,
    		Run: func(ccmd *cobra.Command, args []string) {
    
    			spew.Dump(viper.GetString("name"))
    			spew.Println("")
    
    			fmt.Println("GetStringMap")
    			spew.Dump(viper.GetStringMap("items"))
    
    			fmt.Println("")
    
    			fmt.Println("GetStringMapString")
    			spew.Dump(viper.GetStringMapString("items"))
    		},
    	}
    
    	rootCmd.Flags().StringVar(&name, "name", "", "Name of the list")
    	rootCmd.Flags().StringToStringVar(&items, "item", nil, "Map stating the items to be included")
    
    	viper.BindPFlag("name", rootCmd.Flags().Lookup("name"))
    	viper.BindPFlag("items", rootCmd.Flags().Lookup("item"))
    
    	rootCmd.Execute()
    }

If I run this with the command `go run .\main.go --item shopping=apple,banana --name foobar` I get the following result

    (string) (len=6) "foobar"
    
    GetStringMap
    (map[string]interface {}) {
    }
    
    GetStringMapString
    (map[string]string) {
    }

As can be seent he output contains nothing for the items even though I set the input (I believe) correctly. I have been trying to use PR https://github.com/spf13/pflag/pull/133 to work out how to do it but I am not having any luck.

I am wondering if the binding is incorrect, but I have used CObra successfully in other projects so it is my lack of understanding as to how to reference the generated `map[string]string` from Cobra.

---

## Answer

As far as the binding part is concerned, it is correct. However, before processing, you can verify if a particular key exists using [vipver.IsSet()][1], print all the available keys using [viper.AllKeys()][2] or print everything using [viper.AllSettings()][3].

Here's an example (`test.go`):

    package main
    
    import (
    	"fmt"
    
    	"github.com/spf13/cobra"
    	"github.com/spf13/viper"
    )
    
    func main() {
    	var items map[string]string
    
    	rootCmd := &cobra.Command{
    		Use: "app",
    		Run: func(ccmd *cobra.Command, args []string) {
    
    			fmt.Println("item exists?", viper.IsSet("item"))
    			fmt.Println("GetString  :", viper.GetString("item"))
    			fmt.Println("Keys       :", viper.AllKeys())
    			fmt.Println("Settings   :", viper.AllSettings())
    		},
    	}
    
    	rootCmd.Flags().StringToStringVarP(&items, "item", "i", nil, "Map stating the items to be included")
    	viper.BindPFlag("item", rootCmd.Flags().Lookup("item"))
    	rootCmd.Execute()
    }

Output:

    $ ./test.exe -i 'k=v,"a=b,c"'
    item exists? true
    GetString  : [k=v,"a=b,c"]
    Keys       : [item]
    Settings   : map[item:[k=v,"a=b,c"]]

---

The usage of `GetStringMap()` and `GetStringMapString()` makes more sense with other formats like JSON, YAML, etc. You can trace the execution of these functions to JSON unmarshalling calls in debugging mode.

For map conversion, you can write your own function like this ([live][4]):

    func getStringMap(s string) map[string]string {
    	entries := strings.Split(s, ",")
    
    	m := make(map[string]string)
    	for _, e := range entries {
    		tokens := strings.Split(e, "=")
    		k := strings.TrimSpace(tokens[0])
    		v := strings.TrimSpace(tokens[1])
    		m[k] = v
    	}
    
    	return m
    }

  [1]: https://godoc.org/github.com/hyperledger/fabric/vendor/github.com/spf13/viper#IsSet
  [2]: https://godoc.org/github.com/hyperledger/fabric/vendor/github.com/spf13/viper#AllKeys
  [3]: https://godoc.org/github.com/hyperledger/fabric/vendor/github.com/spf13/viper#AllSettings
  [4]: https://play.golang.org/p/w7TCJH8szDP

---
