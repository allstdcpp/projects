local M = {
	"nvim-mini/mini.tabline",
	version = "*",
	config = function()
		require("mini.tabline").setup();
	end
}

return M
