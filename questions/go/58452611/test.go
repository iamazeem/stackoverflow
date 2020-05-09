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
