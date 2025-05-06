//
// Created by carlo on 13/04/2025.
//
void weight_used(OutputData &output) {
    for (auto p : output.pallets) {
       output.totalWeight += p.weight;
    }
}

void exhaustive(OutputData &output, Algorithm &data) {
    int n = data.pallets.size();
    int maxProfit = 0;
    vector<Pallet> bestCombination;

    for (int mask = 0; mask < (1 << n); ++mask) {
        int totalWeight = 0;
        int totalProfit = 0;
        vector<Pallet> currentCombination;

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                totalWeight += data.pallets[i].weight;
                totalProfit += data.pallets[i].profit;
                currentCombination.push_back(data.pallets[i]);
            }
        }


        if (totalWeight <= data.TotalWeight && totalProfit > maxProfit) {
            maxProfit = totalProfit;
            bestCombination = currentCombination;
        }

    }


    output.totalProfit = maxProfit;
    output.pallets = bestCombination;

}

void knapsackDP(OutputData &output, const Algorithm &data) {
    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int w = data.pallets[i - 1].weight;
        int p = data.pallets[i - 1].profit;

        for (int j = 0; j <= maxWeight; ++j) {
            if (w <= j) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + p);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    int j = maxWeight;
    for (int i = n; i > 0; --i) {
        if (dp[i][j] != dp[i - 1][j]) {
            const Pallet &p = data.pallets[i - 1];
            output.pallets.push_back(p);
            output.totalProfit += p.profit;
            j -= p.weight;
        }
    }

    reverse(output.pallets.begin(), output.pallets.end());
}


void knapsackGR(OutputData &output, const Algorithm &data) {
    const int maxWeight = data.TotalWeight;
    const int n = data.pallets.size();

    vector<pair<Pallet, double>> palletsRatio(n);

    for (unsigned int i = 0; i < n; i++) {
        palletsRatio[i] = {data.pallets[i], static_cast<double>(data.pallets[i].profit / data.pallets[i].weight)};
    }

    sort(palletsRatio.begin(), palletsRatio.end(), [](const pair<Pallet,double> &a, const pair<Pallet,double> &b) {
        return a.second > b.second;
    });

    unsigned int currentWeight = 0;

    for (unsigned int i = 0; i < n && currentWeight <= maxWeight; i++) {
        const Pallet cur_pallet = palletsRatio[i].first;
        if (currentWeight + cur_pallet.weight <= maxWeight) {
            output.pallets.push_back(cur_pallet);
            currentWeight += cur_pallet.weight;
            output.totalProfit += cur_pallet.profit;
        }
    }

}