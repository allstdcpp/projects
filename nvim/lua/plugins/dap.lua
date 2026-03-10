local M = {
    "rcarriga/nvim-dap-ui",
    dependencies = {
        "williamboman/mason.nvim",
        "mfussenegger/nvim-dap",
        "nvim-neotest/nvim-nio",
        "theHamsta/nvim-dap-virtual-text"
    },
    config = function()
        local nmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("n", "<Leader>" .. suffix, rhs, { desc = desc })
        end
        local xmap_leader = function(suffix, rhs, desc)
            vim.keymap.set("x", "<Leader>" .. suffix, rhs, { desc = desc })
        end

        local dap = require("dap")
        local bin_directory = vim.fn.stdpath("data") .. "/mason/bin"

        dap.adapters.cppdbg = {
            id = "cppdbg",
            type = "executable",
            command = bin_directory .. "/OpenDebugAD7",
        }

        dap.configurations.cpp = {
            {
                name = "Launch file",
                type = "cppdbg",
                request = "launch",
                program = function()
                    return vim.fn.input("Path to executable: ", vim.fn.getcwd() .. "/", "file")
                end,
                cwd = "${workspaceFolder}",
                stopAtEntry = true,
            },
            {
                name = "Attach to gdbserver :1234",
                type = "cppdbg",
                request = "launch",
                MIMode = "gdb",
                miDebuggerServerAddress = "localhost:1234",
                miDebuggerPath = "/usr/bin/gdb",
                cwd = "${workspaceFolder}",
                program = function()
                    return vim.fn.input("Path to executable: ", vim.fn.getcwd() .. "/", "file")
                end,
            },
        }

        vim.fn.sign_define("DapBreakpoint", {
            text = "⬤",
            texthl = "ErrorMsg",
            linehl = "",
            numhl = "ErrorMsg",
        })

        vim.fn.sign_define("DapBreakpointCondition", {
            text = "⬤",
            texthl = "ErrorMsg",
            linehl = "",
            numhl = "SpellBad",
        })

        nmap_leader("db", function()
            dap.toggle_breakpoint()
        end, "Toggle Breakpoint")

        nmap_leader("dc", function()
            dap.continue()
        end, "Continue")

        nmap_leader("dl", function()
            dap.run_last()
        end, "Run Last")

        local dapui = require("dapui")
        dapui.setup({})

        dap.listeners.before.attach.dapui_config = function()
            dapui.open()

            nmap_leader("do", function()
                dap.step_over()
            end, "Step Over")

            nmap_leader("di", function()
                dap.step_into()
            end, "Step Into")

            nmap_leader("df", function()
                dap.step_out()
            end, "Step Out")

            nmap_leader("dr", function()
                dap.repl.open()
            end, "Repl")
        end
        dap.listeners.before.launch.dapui_config = function()
            dapui.open()
        end
        dap.listeners.before.event_terminated.dapui_config = function()
            dapui.close()
        end
        dap.listeners.before.event_exited.dapui_config = function()
            dapui.close()
        end
    end,
}

return M
