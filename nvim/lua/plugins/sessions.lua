local M = {
    "jedrzejboczar/possession.nvim",
    dependencies = { "nvim-lua/plenary.nvim", "nvim-telescope/telescope.nvim" },
    config = function()
        require("possession").setup({})
        require("telescope").load_extension("possession")
    end,
}

return M
