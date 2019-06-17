defmodule HottspotCapital.IexApiClientTest do
  use HottspotCapital.Test.MockCase

  alias HottspotCapital.IexApiClient
  alias HottspotCapital.Test.Stubs.IexApiStubs
  alias HottspotCapital.Test.Utils

  describe ".fetch_stock_quote" do
    test "retries 502 response of GET /stock/<symbol>/quote" do
      DynamicMocks.update(%{
        function: :get_symbols,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: [IexApiStubs.base_symbol("HOTT")]
      })

      DynamicMocks.update(%{
        function: :get_stock,
        module: HottspotCapital.Test.Mocks.IexApiClient,
        value: {:ok, %{body: %{}, status_code: 502}}
      })

      Utils.with_env(
        :hottspot_capital,
        :iex_api_client,
        [request_retry_wait: 1],
        fn ->
          assert IexApiClient.fetch_stock_quote("HOTT") == nil
        end
      )
    end
  end
end
